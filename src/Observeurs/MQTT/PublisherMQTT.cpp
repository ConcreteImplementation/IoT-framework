#include <string.h>

#include <esp_system.h>

#include <ArduinoJson.h>

#include "Observeurs/MQTT/PublisherMQTT.h"
#include "Observeurs/MQTT/threadCallbacks.h"



// #define BASSE_PRIORITE() usleep(250 * 1000)

// static void* staticSeConnecterThreadCallback(void* arg) {
// 	BASSE_PRIORITE();

// 	Serial.println("DEB staticSeConnecterThreadCallback");
// 	PublisherMQTT* mqtt = (PublisherMQTT*) arg;
// 	mqtt->seConnecter();
// 	Serial.println("                FIN staticSeConnecterThreadCallback");

// 	return nullptr;
// }

// static void* staticPublierThreadCallback(void* arg) {
// 	BASSE_PRIORITE();

// 	PublisherMQTT* mqtt = (PublisherMQTT*) arg;
// 	mqtt->publier();

// 	return nullptr;
// }

PublisherMQTT::PublisherMQTT()
	: m_minuterie(1000),
		m_estWiFiConnecte(false),
		m_estMQTTConnecte(false),
		m_estEnConnexionWiFi(false),
		m_estEnPublication(false)
{ 
	ajouterParametre(
		"AdresseIPCourtier",
		"Adresse IP du courtier",
		"000.000.000.000",
		strlen("000.000.000.000")
	);
	ajouterParametre(
		"NomUtilisateur",
		"Nom utilisateur MQTT",
		"Nom utilisateur MQTT",
		50
	);
	ajouterParametre(
		"MotDePasse",
		"Mot de passe MQTT",
		"123456789",
		50
	);
}



void PublisherMQTT::configurer() {
	IPAddress adresseCourtier;
	adresseCourtier.fromString( getValeur("AdresseIPCourtier") );
	m_publisher = new PubSubClient(adresseCourtier, 1883, m_wifiClient);	


	_genererGuid();
	m_temperature = new ConfigurationHomeAssistant(m_guid, "temperature", "°C", "temperature");
	m_pression    = new ConfigurationHomeAssistant(m_guid, "pressure",    "Pa", "pression");
	m_luminosite  = new ConfigurationHomeAssistant(m_guid, "illuminance",  "",  "luminosite");
	
	pthread_mutex_init(&m_mutexConnexion, NULL);
	pthread_mutex_init(&m_mutexPublication, NULL);
	pthread_attr_init(&m_attribut);
	pthread_attr_setdetachstate(&m_attribut, PTHREAD_CREATE_DETACHED);
	pthread_create(&m_thread, &m_attribut, staticSeConnecterThreadCallback, this);

	Serial.println("Depuis Senseur: ");
	Serial.println(adresseCourtier);
	Serial.println( getValeur("NomUtilisateur"));
	Serial.println( getValeur("MotDePasse"));
	Serial.println(m_guid);
	Serial.println(WiFi.localIP());
}



void PublisherMQTT::_genererGuid() {
	uint8_t mac[6];
	esp_read_mac(mac, ESP_MAC_WIFI_STA);
	for(int i = 0; i < 5; ++i) {
		for(int j = 0; j < 4; ++j) {
			mac[i] ^=	WiFi.localIP()[j];
		}
	}
	snprintf(m_guid, 16, "SMG%02X%02X%02X%02X%02X%02X", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
}



void PublisherMQTT::notifier(Message* p_message) {
	_verifierEtat(p_message);
	
	if(m_minuterie.estTermine()) {
		m_minuterie.redemarrer();
		_publierAsync(p_message);
	}
}


void PublisherMQTT::_verifierEtat(Message* p_message) {
int etat = m_publisher->state();
	if( etat != 0) {
		const char* erreur = _erreurVersChaine(etat);
		p_message->ajouterMessage(erreur);
	}

	if(m_estWiFiConnecte == false) {
		p_message->ajouterMessage("wifi connexion");
	}

	if(m_estMQTTConnecte == false) {
		p_message->ajouterMessage("mqtt connexion");
	}
}


void PublisherMQTT::_publierAsync(Message* p_message) {
	int resultat = pthread_mutex_trylock(&m_mutexPublication);
	
	if( resultat != EBUSY) {
		m_message = *p_message;

		pthread_join(m_thread, NULL);
		int reussi = pthread_create(&m_thread, &m_attribut, staticPublierThreadCallback, this);
		if( reussi != 0 ) {
			Serial.println("Incapable de créer la thread de publication");
		}
	}
}


void PublisherMQTT::publier() {
	m_estMQTTConnecte = m_publisher->publish(m_guid, m_message.versJson());
		if( ! m_estMQTTConnecte ) { seConnecter(); }

	m_estMQTTConnecte = m_publisher->publish(m_temperature->getSujet(), m_temperature->getCharge());
		if( ! m_estMQTTConnecte ) { seConnecter(); }
	m_estMQTTConnecte = m_publisher->publish(m_pression->getSujet(),    m_pression->getCharge());
		if( ! m_estMQTTConnecte ) { seConnecter(); }
	m_estMQTTConnecte = m_publisher->publish(m_luminosite->getSujet(),  m_luminosite->getCharge());
		if( ! m_estMQTTConnecte ) { seConnecter(); }

	m_estEnPublication = false;
	pthread_mutex_unlock(&m_mutexPublication);
}


void PublisherMQTT::seConnecter() {
	int retour = pthread_mutex_trylock(&m_mutexConnexion);
	if( retour == EBUSY) { return; }

	do {
		m_estWiFiConnecte = m_publisher->connect( m_guid, getValeur("NomUtilisateur"), getValeur("MotDePasse") );
	} while(m_estWiFiConnecte == false);

	pthread_mutex_unlock(&m_mutexConnexion);
}





const char* PublisherMQTT::_erreurVersChaine(int p_etat) {
	const char* message = "";
	switch(p_etat) {
											// 0123456789ABCDF
		case -2 : message = "MQTT Reseau";     break; // Si réinitialise le courtier, ou HA n'est plus sur le réseau ou mauvaise IP courtier
		case -1 : message = "MQTT Connexion";  break; // Deconnecté, ou pas encore connecté
		case  5 : message = "MQTT client/mdp"; break; // après test sur HA: utilisateur inexistant ou mdp incorrect
  	
		case  0 : message = "MQTT OK."; break;

		case -4 : message = "MQTT Courtier";   break; // Aucune reponse du courtier durant le delais d'attente.
		case -3 : message = "MQTT Connexion";  break; // reseau brisee 
		case  1 : message = "MQTT Version";    break; // Le serveur ne supporte pas cette version de requete MQTT
		case  2 : message = "MQTT Rejet";      break; // Le serveur a rejeter l'identifiant du client
		case  3 : message = "MQTT Inaccepte";  break; // Le serveur n'a pu accepter la connexion
		case  4 : message = "MQTT client/mdp"; break; // Nom utilisateur ou mot de passe rejete
		default : message = "MQTT Inatendu";   break;
	}
	return message;
}
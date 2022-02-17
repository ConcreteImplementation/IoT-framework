#include <SPIFFS.h>
#include <ArduinoJson.h>

#include "Cadriciel/ConfigurationWiFi.h"
#include "Cadriciel/Message.h"


const char* Portail_SSID = "StationMeteoGeniale";
const char* Portail_PASS = "12345678";
IPAddress adressePortail(192, 168, 23, 1);
IPAddress adressePasserelle(192, 168, 23, 1);
IPAddress masqueReseau(255, 255, 255, 0);

ConfigurationWiFi::ConfigurationWiFi(bool p_estModeDebug)
	:	m_wifiManager()
{
	m_wifiManager.setDebugOutput(p_estModeDebug);
	m_wifiManager.setConfigPortalTimeout(180);
	m_wifiManager.setAPStaticIPConfig(adressePortail, adressePasserelle, masqueReseau);
	// m_wifiManager.setAPCallback([](WiFiManager* p_wifiManager) {
	// 	Serial.println("Echec de la connexion au reseau. Lancement de WiFiManager.");
	// });
	m_wifiManager.setParamsPage(true);
	m_wifiManager.setSaveParamsCallback([this] {
		this->_callbackPourSetSaveParams();
	});
}



void ConfigurationWiFi::ajouterParametre(AbstractConfigurable* p_configurable) {
	p_configurable->chargerParametres( &m_wifiManager );
}
void ConfigurationWiFi::demarrer(Message* p_message) {	
	m_wifiManager.autoConnect(Portail_SSID, Portail_PASS);


	_chargerLesValeurs();	

	if(WiFi.isConnected() == false) {
		p_message->ajouterMessage("configuration wifi: erreur connexion reseau.");
		return;
	}

	p_message->ajouterMessage("connexion reseau reussie.");
}



void ConfigurationWiFi::_callbackPourSetSaveParams() {
	Serial.println("SAUVEGARDE PARAMETRES");

	SPIFFS.begin();

	WiFiManagerParameter** parametres = m_wifiManager.getParameters();
	WiFiManagerParameter** fin = parametres + m_wifiManager.getParametersCount();
	DynamicJsonDocument document(2048);
	
	Serial.println("Parametres: ");
	while(parametres < fin) {
		const char* nom = (*parametres)->getLabel();
		const char* valeur = (*parametres)->getValue();

		Serial.print(nom);
		Serial.print(" : ");
		Serial.println(valeur);

		document[nom] = valeur;
		++parametres;
	}

	Serial.println("Ecriture... ");
	char resultatJson[2048];
	serializeJson(document, resultatJson);
	File fichierConfigurations = SPIFFS.open("/configurations.json", "w");
	fichierConfigurations.println(resultatJson);
	fichierConfigurations.close();

	Serial.println("Fichier: ");
	fichierConfigurations = SPIFFS.open("/configurations.json", "r");
	Serial.println(fichierConfigurations.readString());
	fichierConfigurations.close();
}






void ConfigurationWiFi::_chargerLesValeurs() {
	Serial.println("CHARGEMENT PARAMETRES");

	SPIFFS.begin();
	
	File fichierConfigurations = SPIFFS.open("/configurations.json", "r");
	DynamicJsonDocument document(2048);
	DeserializationError erreur = deserializeJson(document, fichierConfigurations);
	if(erreur) {
		Serial.println("Erreur lors du chargement des parametres");
		return;
	}
	fichierConfigurations.close();

	WiFiManagerParameter** parametres = m_wifiManager.getParameters();
	WiFiManagerParameter** fin = parametres + m_wifiManager.getParametersCount();

	Serial.println("Parametres: ");
	while(parametres < fin) {
		const char* nom = (*parametres)->getLabel();
		int longueur = (*parametres)->getValueLength();
		const char* valeur = document[nom];
		(*parametres)->setValue(valeur, longueur);

		Serial.print(nom);
		Serial.print(" : ");
		Serial.println((*parametres)->getValue());

		++parametres;
	}
}

	

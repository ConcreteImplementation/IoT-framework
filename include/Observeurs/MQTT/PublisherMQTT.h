#pragma once

#include <pthread.h>

#include <WiFi.h>
#include <PubSubClient.h>

#include "Cadriciel/IObserveur.h"
#include "Cadriciel/AbstractConfigurable.h"
#include "Cadriciel/Minuterie.h"
#include "Observeurs/MQTT/ConfigurationHomeAssistant.h"

class PublisherMQTT: public IObserveur, public AbstractConfigurable {
private:
	Minuterie m_minuterie;
	Message m_message;

	WiFiClient m_wifiClient;
	bool m_estWiFiConnecte;
	bool m_estMQTTConnecte;
	
	PubSubClient* m_publisher;
	char m_guid[16];
	char* m_sujet[20];
	ConfigurationHomeAssistant* m_temperature;
	ConfigurationHomeAssistant* m_pression;
	ConfigurationHomeAssistant* m_luminosite;	

	pthread_t       m_thread;
	pthread_attr_t  m_attribut;
	pthread_mutex_t m_mutexConnexion;
	pthread_mutex_t m_mutexPublication;
	bool m_estEnConnexionWiFi;
	bool m_estEnPublication;


	void _genererGuid();
	void _genererSujet();

	void _verifierEtat(Message* p_message);
	void _publierAsync(Message* p_message);

	const char* _erreurVersChaine(int p_etat);


public:
	PublisherMQTT();

	void configurer()                 override;
	void notifier(Message* p_message) override;
	
	void seConnecter();
	void publier();
};
#pragma once 

#include <list>

#include <WiFiManager.h>
#include "Cadriciel/AbstractConfigurable.h"

class ConfigurationWiFi {
private:
	WiFiManager m_wifiManager;
	std::list<WiFiManagerParameter> m_parametres;
	bool m_aNouvellesValeurs;


	void _callbackPourSetSaveParams();

	void _chargerLesValeurs();

public:
	ConfigurationWiFi(bool p_estModeDebug);
	
	void ajouterParametre(AbstractConfigurable* p_configurable);
	void demarrer(Message* p_message);
	
	void tick();
};
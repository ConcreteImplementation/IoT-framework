#pragma once

#include <map>

#include <WiFiManager.h>

#include "Cadriciel/Message.h"

class AbstractConfigurable {
private:
	std::map<const char*, WiFiManagerParameter*> m_parametres;
	
protected:
	WiFiManagerParameter* m_parametre;

	void ajouterParametre(
		const char* p_id,
		const char* p_label,
		const char* p_defaultValue,
		int p_length
	);

public:
	AbstractConfigurable();
	void chargerParametres(WiFiManager* p_wifimanager);
	const char* getValeur(const char* p_nomParametre);
	
	virtual void configurer() = 0;
};
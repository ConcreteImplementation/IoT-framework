#include "Cadriciel/AbstractConfigurable.h"


AbstractConfigurable::AbstractConfigurable()
{ ; }



void AbstractConfigurable::ajouterParametre(
	const char* p_id,
	const char* p_label,
	const char* p_defaultValue,
	       int  p_length
	)	{
	WiFiManagerParameter* parametre =
		new WiFiManagerParameter(p_id, p_label, p_defaultValue, p_length);
	
	std::pair<const char*, WiFiManagerParameter*> entree(p_id, parametre);

	m_parametres.insert( entree );
}

void AbstractConfigurable::chargerParametres(WiFiManager* p_wifimanager) {
	std::map<const char*, WiFiManagerParameter*>::iterator it = m_parametres.begin();
	while(it != m_parametres.end()) {
		p_wifimanager->addParameter( (*it).second );
		++it;
	}
}

const char* AbstractConfigurable::getValeur(const char* p_nomParametre) {
	return m_parametres[p_nomParametre]->getValue();
}


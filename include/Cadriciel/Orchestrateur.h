#pragma once

#include <list>


#include "Cadriciel/AbstractConfigurable.h"
#include "Cadriciel/ISenseur.h"
#include "Cadriciel/IObserveur.h"
#include "Cadriciel/ConfigurationWiFi.h"
#include "Cadriciel/Bouton.h"
#include "Cadriciel/ActionReinitialisation.h"

class Orchestrateur {
private:
	bool m_estModeDebug;
	Message m_message;
	ConfigurationWiFi m_configurationwifi;
	Bouton m_boutonReset;

	void _configurerConfigurables();
	void _interrogerSenseurs();
	void _notifierObservateurs();


protected:
	std::list<AbstractConfigurable*> m_configurables;
	std::list<ISenseur*> m_senseurs;
	std::list<IObserveur*> m_observeurs;

	virtual void chargerConfigurables() = 0;
	virtual void chargerSenseurs() = 0;
	virtual void chargerObserveurs() = 0;


public:
	Orchestrateur(bool p_estModeDebug, const int& p_borneBoutonReset);
	void setup();
	void loop();
};
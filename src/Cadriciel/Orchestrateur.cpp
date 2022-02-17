#include "Cadriciel/Orchestrateur.h"

#include "Cadriciel/ConfigurationWiFi.h"
#include "Cadriciel/Message.h"
#include "Cadriciel/ActionReinitialisation.h"
#include "Observeurs/AfficheurGenerique.h"


Orchestrateur::Orchestrateur(bool p_estModeDebug, const int& p_borneBoutonReset)
	:	m_estModeDebug(p_estModeDebug),
		m_configurationwifi(p_estModeDebug),
		m_boutonReset(p_borneBoutonReset, nullptr, &staticActionReinitialisation)
	{

		if(m_estModeDebug) {
			Serial.begin(115200);
			while(!Serial) {;}
	}
}



void Orchestrateur::setup() {
	chargerConfigurables();
	_configurerConfigurables();
	chargerSenseurs();
	chargerObserveurs();
	
	if(m_estModeDebug) {
		AfficheurGenerique* afficheur = new AfficheurGenerique(Serial);
		m_observeurs.push_back( afficheur );
	}
}



void Orchestrateur::loop() {
	m_message.vider();
	_interrogerSenseurs();
	_notifierObservateurs();
	
	m_boutonReset.tick();
}



void Orchestrateur::_configurerConfigurables() {
	std::list<AbstractConfigurable*>::iterator it;
	
	it = m_configurables.begin();
	while(it != m_configurables.end()){
		m_configurationwifi.ajouterParametre(*it);
		++it;
	}

	m_configurationwifi.demarrer( & m_message );

	it = m_configurables.begin();
	while(it != m_configurables.end()){
		(*it)->configurer();
		++it;
	}
}

void Orchestrateur::_interrogerSenseurs() {

	std::list<ISenseur*>::iterator it = m_senseurs.begin();
	while(it != m_senseurs.end()){
		(*it)->charger(&m_message);
		++it;
	} 

}

void Orchestrateur::_notifierObservateurs() {
	std::list<IObserveur*>::iterator it = m_observeurs.begin();
		while(it != m_observeurs.end()){
			(*it)->notifier(&m_message);
			++it;
		} 
}
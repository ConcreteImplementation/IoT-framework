#include "Program.h"

#include "Senseurs/SenseurBME.h"
#include "Senseurs/SenseurLuminosite.h"
#include "Senseurs/SenseurThermometre.h"
#include "Senseurs/SenseurMockPression.h"
#include "Senseurs/SenseurMockTemperature.h"




Program::Program(bool p_estModeDebug) 
	: Orchestrateur(p_estModeDebug, BORNE_BOUTON) {

	m_publisherMQTT = new PublisherMQTT();
	m_afficheurKiwi = new AfficheurKiwi();
	m_lcd = new AfficheurLCD();


}

void Program::chargerConfigurables() {
	m_configurables.push_back(m_publisherMQTT);
}


void Program::chargerSenseurs() {
	// m_senseurs.push_back( new SenseurBME() );
	// m_senseurs.push_back( new SenseurThermometre(BORNE_THERMOMETRE) );

	m_senseurs.push_back( new SenseurMockTemperature() );
	m_senseurs.push_back( new SenseurMockPression() );
	m_senseurs.push_back( new SenseurLuminosite(BORNE_PHOTOCELL) );
}

void Program::chargerObserveurs() {
	m_observeurs.push_back(m_publisherMQTT);
	m_observeurs.push_back(m_afficheurKiwi);
	m_observeurs.push_back(m_lcd);
}  


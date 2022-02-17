#include "Senseurs/SenseurMockTemperature.h"


SenseurMockTemperature::SenseurMockTemperature()
	:	m_minuterie(DIX_SECONDES),
		m_temperature(-50)
{ ; }

void SenseurMockTemperature::charger(Message* p_message) {
	p_message->ajouterDonnee("temperature", m_temperature);
	
	if(m_minuterie.estTermine()) {
		 m_minuterie.redemarrer();

		   m_temperature += 10;
		if(m_temperature >= 50)
			 m_temperature = -50;
		
	}
}

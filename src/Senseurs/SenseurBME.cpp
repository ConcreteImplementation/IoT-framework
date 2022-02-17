#include "Senseurs/SenseurBME.h"

#include <SPI.h>
#include <Wire.h>


SenseurBME::SenseurBME()
	: m_messageErreur(nullptr) {
	Wire.begin();
	m_bme.begin();

	for(int i = 0; i < 10 && !m_bme.begin(); ++i) {
		delay(1000);
	}
	if(!m_bme.begin()) {
		m_messageErreur = "BME non trouve";
		return;
	}

	if(m_bme.chipModel() != BME280::ChipModel_BME280
	&& m_bme.chipModel() != BME280::ChipModel_BMP280) {
		m_messageErreur = "BEM inconnu";
	}
}

void SenseurBME::charger(Message* p_message) {
	if(m_messageErreur != nullptr) {
		p_message->ajouterMessage(m_messageErreur);
		return;
	}

	p_message->ajouterDonnee("temperature", m_bme.temp());
	p_message->ajouterDonnee("pression",   m_bme.pres());
}




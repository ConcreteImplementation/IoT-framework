#include <Arduino.h>

#include "Senseurs/SenseurLuminosite.h"


SenseurLuminosite::SenseurLuminosite(const int& p_borne) 
	: m_borne(p_borne)
{ ; }

void SenseurLuminosite::charger(Message* p_message) {
	float luminosite = analogRead(m_borne);
	luminosite /= 4095;
	p_message->ajouterDonnee("luminosite", luminosite);
}
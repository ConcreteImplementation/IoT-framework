#include <Arduino.h>

#include "Senseurs/SenseurMockPression.h"



void SenseurMockPression::charger(Message* p_message) {
	float pression = 1024 + random(-20, 20);
	p_message->ajouterDonnee("pression", pression);
}
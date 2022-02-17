#include <Arduino.h>

#include "Senseurs/SenseurThermometre.h"


SenseurThermometre::SenseurThermometre(const int& p_borne) 
	: m_borne(p_borne)
{ ; }


#define AJUSTEMENT 2
void SenseurThermometre::charger(Message* p_message) {
	float lecture = analogRead(m_borne);
	float voltage = lecture / 4095.0 * 3.3;
	float temperature = (voltage - 0.5) * 100.0 * AJUSTEMENT;
	p_message->ajouterDonnee("temperature", temperature);

	p_message->ajouterDonnee("lecture", lecture);
	p_message->ajouterDonnee("voltage", voltage);

}
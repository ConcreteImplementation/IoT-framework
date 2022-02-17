#pragma once


#include "Cadriciel/Minuterie.h"
#include "Cadriciel/ISenseur.h"

class SenseurMockTemperature : public ISenseur {
private:
	Minuterie m_minuterie;
	float m_temperature;

public:
	SenseurMockTemperature();
	void charger(Message* p_message) override;
};
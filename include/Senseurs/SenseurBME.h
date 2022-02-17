#pragma once

#include <BME280I2C.h>

#include "Cadriciel/ISenseur.h"

class SenseurBME : public ISenseur {
private:
	BME280I2C m_bme;
	const char* m_messageErreur;

public:
	SenseurBME();
	void charger(Message* p_message) override; 
};
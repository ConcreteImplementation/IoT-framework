#pragma once

#include "Cadriciel/ISenseur.h"

class SenseurThermometre : public ISenseur {
private:
	int m_borne;

public:
	SenseurThermometre(const int& p_borne);
	void charger(Message* p_message) override;
};
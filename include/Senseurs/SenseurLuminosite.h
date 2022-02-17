#pragma once

#include "Cadriciel/ISenseur.h"

class SenseurLuminosite : public ISenseur {
private:
	int m_borne;

public:
	SenseurLuminosite(const int& p_borne);
	void charger(Message* p_message) override;
};
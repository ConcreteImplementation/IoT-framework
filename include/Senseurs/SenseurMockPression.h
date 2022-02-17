#pragma once

#include "Cadriciel/ISenseur.h"

class SenseurMockPression : public ISenseur {

public:
	void charger(Message* p_message) override;
};
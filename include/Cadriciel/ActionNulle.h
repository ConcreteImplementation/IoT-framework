#pragma once

#include "Cadriciel/IAction.h"

class ActionNulle : public IAction {
public:
	ActionNulle();
	void executer() override;
};


static ActionNulle staticActionNulle; // ok, classe sans état
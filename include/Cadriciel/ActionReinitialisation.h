#pragma once

#include "Cadriciel/IAction.h"

class ActionReinitialisation : public IAction {
public:
	ActionReinitialisation();
	void executer() override;
};

static ActionReinitialisation staticActionReinitialisation;  // ok, classe sans état
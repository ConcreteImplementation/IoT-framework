#pragma once

#include "Message.h"

class ISenseur {
public:
	virtual void charger(Message* p_message) = 0;
};
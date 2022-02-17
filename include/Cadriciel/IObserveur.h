#pragma once

#include "Message.h"

class IObserveur {
public:
	virtual void notifier(Message* p_message) = 0;
};
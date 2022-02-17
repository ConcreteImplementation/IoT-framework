#pragma once

#include "Cadriciel/Orchestrateur.h"

#include "Observeurs/MQTT/PublisherMQTT.h"
#include "Observeurs/AfficheurKiwi.h"
#include "Observeurs/AfficheurLCD.h"


class Program : public Orchestrateur {
private:
	PublisherMQTT* m_publisherMQTT;
	AfficheurKiwi* m_afficheurKiwi;
	AfficheurLCD* m_lcd;

	void chargerConfigurables() override;
	void chargerSenseurs()      override;
	void chargerObserveurs()    override;

public:
	Program(bool p_estModeDebug);
};
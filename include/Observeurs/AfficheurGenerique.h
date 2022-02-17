#pragma once

#include <list>

#include <Arduino.h>

#include "Cadriciel/IObserveur.h"
#include "Cadriciel/Minuterie.h"

class AfficheurGenerique : public IObserveur {
private:
	Stream& m_sortie;
	Minuterie m_minuterie;
	std::list<const char*> m_erreurs;


public:
	AfficheurGenerique(Stream& p_sortie);

	void notifier(Message* p_message) override;
};
#pragma once

#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#include "Cadriciel/IObserveur.h"
#include "Cadriciel/Minuterie.h"

class AfficheurLCD : public IObserveur {
private:
	LiquidCrystal_I2C* m_lcd;
	Minuterie m_minuterie;
	String m_temperature;
	String m_pression;
	String m_luminosite;
	String m_message;

	void _obtenirDonnees(Message* p_message);
	void _afficherDonnees();

public:
	AfficheurLCD();
	void notifier(Message* p_message) override;
};
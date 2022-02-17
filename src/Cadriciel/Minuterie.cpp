#include <Arduino.h>

#include "Cadriciel/Minuterie.h"



Minuterie::Minuterie(unsigned long p_delais)
	: m_delais(p_delais),
		m_debut (millis())
	{;}


unsigned long Minuterie::getDelais() const {
	return this->m_delais;
}
void Minuterie::setDelais(unsigned long p_delais) {
	this->m_delais = p_delais;
}


bool Minuterie::estTermine() const {
	return millis() - this->m_debut > this->m_delais;
}
void Minuterie::redemarrer() {
	this->m_debut = millis();
}

unsigned long Minuterie::getTempsEcoule() const {
	return millis() - this->m_debut;
}
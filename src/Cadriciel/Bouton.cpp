#include <Arduino.h>

#include "Cadriciel/Bouton.h"
#include "Cadriciel/ActionNulle.h"



Bouton::Bouton(const int &p_borne, IAction* p_actionEnfonce, IAction* p_actionRelache)
	: m_borne             (p_borne),
		m_actionEnfonce     (p_actionEnfonce ? p_actionEnfonce : &staticActionNulle ),
		m_actionRelache     (p_actionRelache ? p_actionRelache : &staticActionNulle ),
		m_minuterie         (Minuterie(50)),
		m_etatActuel        (LOW),
		m_dernierEtat       (HIGH),
		m_dernierEtatStable (HIGH)
{
	pinMode(this->m_borne, INPUT);
}



bool Bouton::_estEtatChange() {
	return this->m_etatActuel != this->m_dernierEtat;
}
bool Bouton::_aEtePresse() {
	return this->m_dernierEtatStable == HIGH && this->m_etatActuel == LOW;
}
bool Bouton::_aEteLeve() {
	return this->m_dernierEtatStable == LOW && this->m_etatActuel == HIGH;
}



int Bouton::getEtat() {
	this->m_etatActuel =  digitalRead(this->m_borne);
	return this->m_etatActuel;
}



void Bouton::tick() {
	this->getEtat();

	if( this->_estEtatChange() ) {
		this->m_minuterie.redemarrer();
		this->m_dernierEtat = this->m_etatActuel;
	}
	else if( this->m_minuterie.estTermine() ) {
		if(this->_aEtePresse()) {
			this->	m_actionEnfonce->executer();
		}
		else if(this->_aEteLeve()) {
			this->m_actionRelache->executer();
		}

		this->m_dernierEtatStable = this->m_etatActuel;
	}
}
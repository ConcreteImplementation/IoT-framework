#pragma once

#include "Cadriciel/IAction.h"
#include "Cadriciel/Minuterie.h"


class Bouton {
private:
	int m_borne;
	IAction* m_actionEnfonce;
	IAction* m_actionRelache;

	Minuterie m_minuterie;

	int m_etatActuel;
	int m_dernierEtat;
	int m_dernierEtatStable;
	
	bool _estEtatChange();
	bool _aEteLeve();
	bool _aEtePresse();

public:
	Bouton(const int &p_borne, IAction* p_actionEnfonce, IAction* p_actionRelache);
	int getEtat();
	
	void tick();
};
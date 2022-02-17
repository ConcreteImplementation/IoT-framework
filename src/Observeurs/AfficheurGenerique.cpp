#include "Observeurs/AfficheurGenerique.h"


AfficheurGenerique::AfficheurGenerique(Stream& p_sortie)
	: m_sortie(p_sortie),
		m_minuterie(3000)
{ 
	m_minuterie.redemarrer();
	m_sortie.println("On commence!");
}

void AfficheurGenerique::notifier(Message* p_message) {
	if(m_minuterie.estTermine() == false) {
		return;
	}
	m_minuterie.redemarrer();

	m_sortie.println("\nMessage: ");
	m_sortie.println( p_message->versJson() );
	
	m_erreurs.clear();
}


/*
	source : concat lists erreurs dans m_erreur
	https://stackoverflow.com/questions/1449703/how-to-append-a-listt-object-to-another
*/
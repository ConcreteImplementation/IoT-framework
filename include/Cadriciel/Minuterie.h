#pragma once

#define UNE_SECONDE			( 1000UL)
#define CINQ_SECONDES   ( 5000UL)
#define DIX_SECONDES    (10000UL)
#define QUINZE_SECONDES (15000UL)
#define VINGT_SECONDES  (20000UL)
#define TRENTE_SECONDES (30000UL)


class Minuterie {
private:
	unsigned long m_delais;
	unsigned long m_debut;

public:
	Minuterie(unsigned long p_delais);
	
	unsigned long getDelais() const;
	void setDelais(unsigned long p_delais);

	bool estTermine() const;
	void redemarrer();
	unsigned long getTempsEcoule() const;
};
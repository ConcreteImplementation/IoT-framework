#include "Observeurs/AfficheurLCD.h"

AfficheurLCD::AfficheurLCD()
	: m_lcd(new LiquidCrystal_I2C(0x27, 2, 16)),
		m_minuterie(500)
{
	m_lcd->init();
	m_lcd->backlight();
	m_lcd->home();	
	m_lcd->print("      SMG!      ");
	m_lcd->setCursor(0, 1);
	m_lcd->print("En configuration");
}


void AfficheurLCD::notifier(Message* p_message) {
	if(m_minuterie.estTermine() == false) {
		return;
	}
	m_minuterie.redemarrer();

	_obtenirDonnees(p_message);
	_afficherDonnees();
}



void AfficheurLCD::_obtenirDonnees(Message* p_message){
	float temperature = 0.0;
	m_temperature = p_message->reussitObtenir("temperature", &temperature)
		? String((int)temperature) + " C"
		: "?? C"
		;

	float pression = 0.0;
	m_pression = p_message->reussitObtenir("pression", &pression)
		? String((int)pression) + "Pa"
		: "??Pa"
		;

	float luminosite = 0.0;
	m_luminosite =  p_message->reussitObtenir("luminosite", &luminosite)
		? String( (int)(luminosite*100)) + " %"
		: "?? %"
		;

	m_message = p_message->obtenirPremiereErreur();
	if(m_message == "") {
				m_message = luminosite < 0.1 ? "Bonne nuit      " : "Bonjour!        ";
	}
}

void AfficheurLCD::_afficherDonnees(){
	m_lcd->clear();
	m_lcd->home();	
	m_lcd->print(m_temperature + " " +  m_pression + " " +  m_luminosite);
	m_lcd->setCursor(0, 1);
	m_lcd->print(m_message);
}


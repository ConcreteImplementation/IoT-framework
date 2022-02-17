#include <ArduinoJson.h>

#include "Observeurs/AfficheurKiwi.h"

#include "Animations/Animation_1.h"
#include "Animations/Animation_2.h"
#include "Animations/Animation_3.h"
#include "Animations/Animation_4.h"
#include "Animations/Animation_5.h"

AfficheurKiwi::AfficheurKiwi() :  m_minuterieAfficherDonnes(3000)
{
    m_afficheur.afficherTexte("Station meteo geniale!",80,5,2,TFT_BLACK,true);
    m_minuterieAfficherDonnes.redemarrer();
}

void AfficheurKiwi::notifier(Message* p_message)
{
		
    const char* erreur = p_message->obtenirPremiereErreur();
		if(strcmp(erreur, "") == 0) { 
			m_afficheur.effacer(5,21,175,30);
		}
    else if(m_minuterieAfficherDonnes.estTermine()) {
			afficherErreur(erreur);   
    }

    if(m_minuterieAfficherDonnes.estTermine())
    {
			p_message->reussitObtenir("temperature", &m_temperature) ? afficherTemperature(String(m_temperature) + " C") : afficherTemperature("NaN C");
			p_message->reussitObtenir("pression", &m_pression) ? afficherPression(String(m_pression) + " hPa") : afficherPression("NaN hPa");
			m_minuterieAfficherDonnes.redemarrer();
    }
    p_message->reussitObtenir("luminosite", &m_luminosite); 
    afficherAnimation();
}

void AfficheurKiwi::afficherTemperature(String p_temperature)
{
    const char* temperature = p_temperature.c_str();
    m_afficheur.effacer(5, 64, 90, 20);
    m_afficheur.afficherTexte(temperature, 5, 64, 2, TFT_BLACK);
}

void AfficheurKiwi::afficherPression(String p_pression)
{
    const char* pression = p_pression.c_str();
    m_afficheur.effacer(5, 88, 75, 15);
    m_afficheur.afficherTexte(pression, 5, 88, 2, TFT_BLACK);
}

void AfficheurKiwi::afficherAnimation()
{
    const unsigned short** animation = nullptr;
    if(m_luminosite < 0.1) {animation = animation5; }
    else if(m_temperature <= -25) {animation = animation1; }
    else if(m_temperature < 0 && m_temperature > -25) {animation = animation2; }
    else if(m_temperature >= 0 && m_temperature < 25) {animation = animation3; }
    else if(m_temperature >= 25) {animation = animation4; }
    else {animation = animation3; }
    m_afficheur.afficherAnimation(animation, 90, 50, 64, 80);
}

void AfficheurKiwi::afficherErreur(const char* p_erreur)
{
    m_afficheur.effacer(5,21,175,30);
    m_afficheur.afficherTexte("*** Erreur ***",80,18,2,TFT_RED,true);
    m_afficheur.afficherTexte(p_erreur,80,30,2,TFT_BLACK, true);
}
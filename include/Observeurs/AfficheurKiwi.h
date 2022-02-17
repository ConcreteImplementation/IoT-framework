#pragma once

#include <Arduino.h>
#include <TFT_eSPI.h>

#include "Cadriciel/IObserveur.h"
#include "Cadriciel/Minuterie.h"
#include "Observeurs/AfficheurOLED.h"

class AfficheurKiwi : public IObserveur 
{
    private:
        AfficheurOLED m_afficheur = AfficheurOLED();
        Minuterie m_minuterieAfficherDonnes;
        float m_temperature = 0;
        float m_pression = 0;
        float m_luminosite = 0;
        std::list<const char*> m_erreurs;

        void afficherTemperature(String p_temperature);
        void afficherPression(String p_pression);
        void afficherAnimation();
        void afficherErreur(const char* p_erreur);
    public:
        AfficheurKiwi();
        void notifier(Message* p_message) override; 
};
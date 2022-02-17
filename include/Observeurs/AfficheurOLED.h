#pragma once

#include <Arduino.h>
#include <TFT_eSPI.h>

#include "Cadriciel/Minuterie.h"

class AfficheurOLED 
{
    private:
        TFT_eSPI m_afficheur = TFT_eSPI();
        Minuterie m_minuterieFrame;
        int m_frame = 1;
        int m_inversionFrame = 1;
    public:
        AfficheurOLED();
        void afficherTexte(const char* p_string, int32_t p_x, int32_t p_y, int8_t p_font, int p_couleur, bool p_estCentre = false);
        void afficherImage(const uint16_t* p_image, int32_t p_x, int32_t p_y, int32_t p_width, int32_t p_height);
        void effacer(int32_t p_x, int32_t p_y, int32_t p_width, int32_t p_height);
        void afficherAnimation(const unsigned short** p_animation, int32_t p_x, int32_t p_y, int32_t p_width, int32_t p_height);
};
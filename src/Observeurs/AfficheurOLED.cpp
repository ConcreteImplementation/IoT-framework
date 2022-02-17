#include "Observeurs/AfficheurOLED.h"

AfficheurOLED::AfficheurOLED(): m_minuterieFrame(1000)
{
    m_afficheur.init();
    m_afficheur.setRotation(1);
    m_afficheur.fillScreen(0xFFDF);
    m_afficheur.setSwapBytes(true);

    m_minuterieFrame.redemarrer();
}

void AfficheurOLED::afficherTexte(const char* p_string, int32_t p_x, int32_t p_y, int8_t p_font, int p_couleur, bool p_estCentre)
{
    m_afficheur.setTextColor(p_couleur);
    if(p_estCentre)
    {
        m_afficheur.drawCentreString(p_string, p_x, p_y, p_font);
    }
    else
    {
        m_afficheur.drawString(p_string, p_x, p_y, p_font);
    }
}

void AfficheurOLED::afficherImage(const uint16_t* p_image, int32_t p_x, int32_t p_y, int32_t p_width, int32_t p_height)
{
    m_afficheur.pushImage(p_x, p_y, p_width, p_height, p_image);
}

void AfficheurOLED::effacer(int32_t p_x, int32_t p_y, int32_t p_width, int32_t p_height)
{
    m_afficheur.fillRect(p_x, p_y, p_width, p_height, 0xFFDF);
}

void AfficheurOLED::afficherAnimation(const unsigned short** p_animation, int32_t p_x, int32_t p_y, int32_t p_width, int32_t p_height)
{
    if(m_minuterieFrame.estTermine())
    {
        m_afficheur.pushImage(p_x, p_y, p_width, p_height, p_animation[m_frame]);
        m_frame += m_inversionFrame;
        if(m_frame == 0 || m_frame == 2)
        {
            m_inversionFrame = -m_inversionFrame;
        }
        m_minuterieFrame.redemarrer();
    }
}
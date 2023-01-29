/*! \file CRoues.cpp
    \brief Implémentationd la classe CRoues pour MBED
*/
#include "CGlobale.h"

#define RESOL_PWM 1024
#define POURCENT2PWM (RESOL_PWM/100.)

//___________________________________________________________________________
/*!
   \brief Constructeur

   \param --
   \return --
*/
CRoues::CRoues() 
{
    resetCodeurs();
}

//___________________________________________________________________________
/*!
   \brief Applique la puissance au moteur gauche

   \param vitesse la vitesse signee en pourcentage [-100%;+100]
   \return --
*/
void CRoues::AdapteCommandeMoteur_G(float vitesse)
{
    if (vitesse > 0) {
        // TODO
        digitalWrite(PIN_Mot1_Sens1, 0);
        digitalWrite(PIN_Mot1_Sens2, 1);
        analogWrite(PIN_Mot1_PWM, vitesse * POURCENT2PWM);
    }
    else if (vitesse < 0) {
        // TODO
        digitalWrite(PIN_Mot1_Sens1, 1);
        digitalWrite(PIN_Mot1_Sens2, 0);
        analogWrite(PIN_Mot1_PWM, -vitesse * POURCENT2PWM);
    }
    else { 					// Mise en court circuit du pont en H
        // TODO
        digitalWrite(PIN_Mot1_Sens1, 1);
        digitalWrite(PIN_Mot1_Sens2, 1);
        analogWrite(PIN_Mot1_PWM, 0);
    }

    m_cde_roue_G = vitesse;
}


//___________________________________________________________________________
/*!
   \brief Applique la puissance au moteur droit

   \param vitesse la vitesse signee en pourcentage [-100%;+100]
   \return --
*/
void CRoues::AdapteCommandeMoteur_D(float vitesse)
{
    if (vitesse > 0) {
        digitalWrite(PIN_Mot2_Sens1, 1);
        digitalWrite(PIN_Mot2_Sens2, 0);
        analogWrite(PIN_Mot2_PWM, vitesse * POURCENT2PWM);
    }
    else if (vitesse < 0) {
        digitalWrite(PIN_Mot2_Sens1, 0);
        digitalWrite(PIN_Mot2_Sens2, 1);
        analogWrite(PIN_Mot2_PWM, -vitesse * POURCENT2PWM);
    }
    else { 					// Mise en court circuit du pont en H
        digitalWrite(PIN_Mot2_Sens1, 1);
        digitalWrite(PIN_Mot2_Sens2, 1);
        analogWrite(PIN_Mot2_PWM, 0);
    }

    m_cde_roue_D = vitesse;
}

//___________________________________________________________________________
/*!
   \brief Renvoie la position du codeur G

   \param --
   \return la position du codeur
*/
int CRoues::getCodeurG(void)
{
    return(Application.m_codeurs.read_CodeurGauche());
}


//___________________________________________________________________________
/*!
   \brief Renvoie la position du codeur D

   \param --
   \return la position du codeur
*/
int CRoues::getCodeurD(void)
{
    return(Application.m_codeurs.read_CodeurDroit());
}


//___________________________________________________________________________
/*!
   \brief Reset les pas cumules par les 2 ccodeurs G et D

   \param --
   \return --
*/
void CRoues::resetCodeurs(void)
{
    Application.m_codeurs.reset_codeurs_G_D();
}

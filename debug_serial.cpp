#include "application.h"
#include "debug_serial.h"


CDebugSerial::CDebugSerial()
{
    m_synchro_logger = false;
    DECLARE_START_PAGE(CDebugSerial::page_principale)
}

void CDebugSerial::send_to_console(char msg[])
{
    Serial.printf("%s", msg);
}

// ====================================================================
//                    PAGES DU MENU
// ====================================================================
void CDebugSerial::page_principale()
{
    DECLARE_PAGE("Menu Principal", CDebugSerial::page_principale)
    DECLARE_OPTION('a', "Commande moteur", CDebugSerial::page_commande_moteurs)
    DECLARE_OPTION('z', "Commande mouvements", CDebugSerial::page_commande_mouvements)
    DECLARE_OPTION('e', "Coeficients Asserv", CDebugSerial::page_reglage_coefs)
    DECLARE_OPTION('c', "Codeurs de position", CDebugSerial::page_codeurs)
    DECLARE_OPTION('l', "Data Logger", CDebugSerial::page_data_logger)
}

void CDebugSerial::page_commande_moteurs()
{
    DECLARE_PAGE("Commande moteurs", CDebugSerial::page_commande_moteurs)
    DECLARE_ACTION('a', "Arrêt moteurs", CDebugSerial::arret_moteurs)

    DECLARE_ACTION('q', "Gauche -50%", CDebugSerial::cde_mot_G_M1)
    DECLARE_ACTION('s', "Gauche -25%", CDebugSerial::cde_mot_G_M2)
    DECLARE_ACTION('d', "Gauche -10%", CDebugSerial::cde_mot_G_M3)

    DECLARE_ACTION('k', "Gauche +10%", CDebugSerial::cde_mot_G_P1)
    DECLARE_ACTION('l', "Gauche +25%", CDebugSerial::cde_mot_G_P2)
    DECLARE_ACTION('m', "Gauche +50%", CDebugSerial::cde_mot_G_P3)


    DECLARE_ACTION('w', "Droit -50%", CDebugSerial::cde_mot_D_M1)
    DECLARE_ACTION('x', "Droit -25%", CDebugSerial::cde_mot_D_M2)
    DECLARE_ACTION('c', "Droit -10%", CDebugSerial::cde_mot_D_M3)

    DECLARE_ACTION('v', "Droit +10%", CDebugSerial::cde_mot_D_P1)
    DECLARE_ACTION('b', "Droit +25%", CDebugSerial::cde_mot_D_P2)
    DECLARE_ACTION('n', "Droit +50%", CDebugSerial::cde_mot_D_P3)


    DECLARE_ACTION('r', "Gauche & Droit -50%", CDebugSerial::cde_mot_GD_M1)
    DECLARE_ACTION('t', "Gauche & Droit -25%", CDebugSerial::cde_mot_GD_M2)
    DECLARE_ACTION('y', "Gauche & Droit -10%", CDebugSerial::cde_mot_GD_M3)

    DECLARE_ACTION('i', "Gauche & Droit +10%", CDebugSerial::cde_mot_GD_P1)
    DECLARE_ACTION('o', "Gauche & Droit +25%", CDebugSerial::cde_mot_GD_P2)
    DECLARE_ACTION('p', "Gauche & Droit +50%", CDebugSerial::cde_mot_GD_P3)
}

void CDebugSerial::page_commande_mouvements()
{
    DECLARE_PAGE("Commande mouvements", CDebugSerial::page_commande_mouvements)
    DECLARE_ACTION('a', "Arrêt moteurs / Asserv manuel", CDebugSerial::arret_moteurs)
    DECLARE_ACTION('q', "CommandeMouvementDistanceAngle(10, 0)", CDebugSerial::cde_distance1)
    DECLARE_ACTION('s', "CommandeMouvementDistanceAngle(20, 0)", CDebugSerial::cde_distance2)
    DECLARE_ACTION('d', "CommandeMouvementDistanceAngle(50, 0)", CDebugSerial::cde_distance3)
    DECLARE_ACTION('f', "CommandeMouvementDistanceAngle(100, 0)", CDebugSerial::cde_distance4)
    DECLARE_ACTION('w', "CommandeMouvementDistanceAngle(0, PI/4.)", CDebugSerial::cde_angle1)
    DECLARE_ACTION('x', "CommandeMouvementDistanceAngle(0, PI/2.)", CDebugSerial::cde_angle2)
    DECLARE_ACTION('c', "CommandeMouvementDistanceAngle(0, PI)", CDebugSerial::cde_angle3)
    DECLARE_ACTION('v', "CommandeMouvementDistanceAngle(0, -PI/4.)", CDebugSerial::cde_angle4)
    DECLARE_ACTION('b', "CommandeMouvementDistanceAngle(0, PI/2.)", CDebugSerial::cde_angle5)
    DECLARE_ACTION('n', "CommandeMouvementDistanceAngle(0, -PI)", CDebugSerial::cde_angle6)
}

void CDebugSerial::page_reglage_coefs()
{
    DECLARE_PAGE("Réglage coefs", CDebugSerial::page_reglage_coefs)
    DECLARE_ACTION('a', "Affiche tous les coefs asserv", CDebugSerial::affiche_coefs_asserv)
    DECLARE_OPTION('q', "Kp_distance", CDebugSerial::page_kp_distance)
    DECLARE_OPTION('s', "Ki_distance", CDebugSerial::page_ki_distance)
    DECLARE_OPTION('d', "Kp_angle", CDebugSerial::page_kp_angle)
    DECLARE_OPTION('f', "Ki_angle", CDebugSerial::page_ki_angle)
}

void CDebugSerial::page_kp_distance()
{
    DECLARE_PAGE("Forçage Kp_distance", CDebugSerial::page_kp_distance)
    DECLARE_OPTION('a', "Retour à la page Coefs", CDebugSerial::page_reglage_coefs)
    DECLARE_ACTION_DOUBLE("Entrez une valeur pour Kp_distance", CDebugSerial::action_set_Kp_distance)
}
void CDebugSerial::page_ki_distance()
{
    DECLARE_PAGE("Forçage Ki_distance", CDebugSerial::page_ki_distance)
    DECLARE_OPTION('a', "Retour à la page Coefs", CDebugSerial::page_reglage_coefs)
    DECLARE_ACTION_DOUBLE("Entrez une valeur pour Ki_distance", CDebugSerial::action_set_Ki_distance)
}
void CDebugSerial::page_kp_angle()
{
    DECLARE_PAGE("Forçage Kp_angle", CDebugSerial::page_kp_angle)
    DECLARE_OPTION('a', "Retour à la page Coefs", CDebugSerial::page_reglage_coefs)
    DECLARE_ACTION_DOUBLE("Entrez une valeur pour Kp_angle", CDebugSerial::action_set_Kp_angle)
}
void CDebugSerial::page_ki_angle()
{
    DECLARE_PAGE("Forçage Ki_angle", CDebugSerial::page_ki_angle)
    DECLARE_OPTION('a', "Retour à la page Coefs", CDebugSerial::page_reglage_coefs)
    DECLARE_ACTION_DOUBLE("Entrez une valeur pour Ki_angle", CDebugSerial::action_set_Ki_angle)
}


void CDebugSerial::page_data_logger()
{
    DECLARE_PAGE("Data Logger", CDebugSerial::page_data_logger)
    DECLARE_ACTION('s', "Start logger", CDebugSerial::start_logger)
    DECLARE_ACTION('t', "Stop logger", CDebugSerial::stop_logger)
    DECLARE_ACTION('p', "Print logger", CDebugSerial::print_logger)
    DECLARE_ACTION('w', "Synchro logger OFF", CDebugSerial::synchro_logger_off)
    DECLARE_ACTION('x', "Synchro logger ON", CDebugSerial::synchro_logger_on)
}

void CDebugSerial::page_codeurs()
{
    DECLARE_PAGE("Codeurs de position", CDebugSerial::page_codeurs)
    DECLARE_ACTION('a', "Affiche position codeurs", CDebugSerial::affiche_codeurs)
    DECLARE_ACTION('r', "RAZ codeurs G & D", CDebugSerial::raz_codeurs)
}


// ====================================================================
//                    ACTIONS
// ====================================================================

bool CDebugSerial::arret_moteurs()  { Application.m_asservissement.CommandeManuelle(0, 0); return true;}
bool CDebugSerial::force_asserv_manuel()  { Application.m_asservissement.ModeAsservissement = CAsservissementBase::cMODE_MANUEL; return true; }
bool CDebugSerial::cde_mot_G_M1()   { force_asserv_manuel(); Application.m_roues.AdapteCommandeMoteur_G(-10); return true; }  // Pour commander une seule roue, on s'assure être en mode asserv manuel
bool CDebugSerial::cde_mot_G_M2()   { force_asserv_manuel(); Application.m_roues.AdapteCommandeMoteur_G(-25); return true; }
bool CDebugSerial::cde_mot_G_M3()   { force_asserv_manuel(); Application.m_roues.AdapteCommandeMoteur_G(-50); return true; }
bool CDebugSerial::cde_mot_G_P1()   { force_asserv_manuel(); Application.m_roues.AdapteCommandeMoteur_G(+10); return true; }
bool CDebugSerial::cde_mot_G_P2()   { force_asserv_manuel(); Application.m_roues.AdapteCommandeMoteur_G(+25); return true; }
bool CDebugSerial::cde_mot_G_P3()   { force_asserv_manuel(); Application.m_roues.AdapteCommandeMoteur_G(+50); return true; }

bool CDebugSerial::cde_mot_D_M1()   { force_asserv_manuel(); Application.m_roues.AdapteCommandeMoteur_D(-10); return true; }
bool CDebugSerial::cde_mot_D_M2()   { force_asserv_manuel(); Application.m_roues.AdapteCommandeMoteur_D(-25); return true; }
bool CDebugSerial::cde_mot_D_M3()   { force_asserv_manuel(); Application.m_roues.AdapteCommandeMoteur_D(-50); return true; }
bool CDebugSerial::cde_mot_D_P1()   { force_asserv_manuel(); Application.m_roues.AdapteCommandeMoteur_D(+10); return true; }
bool CDebugSerial::cde_mot_D_P2()   { force_asserv_manuel(); Application.m_roues.AdapteCommandeMoteur_D(+25); return true; }
bool CDebugSerial::cde_mot_D_P3()   { force_asserv_manuel(); Application.m_roues.AdapteCommandeMoteur_D(+50); return true; }

bool CDebugSerial::cde_mot_GD_M1()   { Application.m_asservissement.CommandeManuelle(-10, -10); return true; }
bool CDebugSerial::cde_mot_GD_M2()   { Application.m_asservissement.CommandeManuelle(-25, -25); return true; }
bool CDebugSerial::cde_mot_GD_M3()   { Application.m_asservissement.CommandeManuelle(-50, -50); return true; }
bool CDebugSerial::cde_mot_GD_P1()   { Application.m_asservissement.CommandeManuelle(+10, +10); return true; }
bool CDebugSerial::cde_mot_GD_P2()   { Application.m_asservissement.CommandeManuelle(+25, +25); return true; }
bool CDebugSerial::cde_mot_GD_P3()   { Application.m_asservissement.CommandeManuelle(+50, +50); return true; }

bool CDebugSerial::cde_distance1()    { Application.m_asservissement.CommandeMouvementDistanceAngle(10, 0); return true; }
bool CDebugSerial::cde_distance2()    { Application.m_asservissement.CommandeMouvementDistanceAngle(20, 0); return true; }
bool CDebugSerial::cde_distance3()    { Application.m_asservissement.CommandeMouvementDistanceAngle(50, 0); return true; }
bool CDebugSerial::cde_distance4()    { Application.m_asservissement.CommandeMouvementDistanceAngle(100, 0); return true; }
bool CDebugSerial::cde_angle1()       { Application.m_asservissement.CommandeMouvementDistanceAngle(0, PI/4.); return true; }
bool CDebugSerial::cde_angle2()       { Application.m_asservissement.CommandeMouvementDistanceAngle(0, PI/2.); return true; }
bool CDebugSerial::cde_angle3()       { Application.m_asservissement.CommandeMouvementDistanceAngle(0, PI); return true; }
bool CDebugSerial::cde_angle4()       { Application.m_asservissement.CommandeMouvementDistanceAngle(0, -PI/4.); return true; }
bool CDebugSerial::cde_angle5()       { Application.m_asservissement.CommandeMouvementDistanceAngle(0, -PI/2.); return true; }
bool CDebugSerial::cde_angle6()       { Application.m_asservissement.CommandeMouvementDistanceAngle(0, -PI); return true; }

bool CDebugSerial::start_logger()       { Application.m_data_logger.start(); return true; }
bool CDebugSerial::stop_logger()        { Application.m_data_logger.stop(); return true; }
bool CDebugSerial::print_logger()       { Application.m_data_logger.print(); return true; }
bool CDebugSerial::synchro_logger_off() { Application.m_asservissement.m_automatic_start_logger = false; return true; }
bool CDebugSerial::synchro_logger_on()  { Application.m_asservissement.m_automatic_start_logger = true; return true; }


// _________________________________________________
bool CDebugSerial::affiche_coefs_asserv()
{
    _printf("Coef distance Kp=%f / Ki=%f\n\r",  Application.m_asservissement.kp_distance,
                                                Application.m_asservissement.ki_distance);

    _printf("Coef angle : Kp=%f / Ki=%f\n\r",   Application.m_asservissement.kp_angle,
                                                Application.m_asservissement.ki_angle);

    return true;
}

// _________________________________________________
bool CDebugSerial::action_set_Kp_distance(double val)
{
    _printf("Changement de la valeur du paramètre kp_distance: %f\n\r", val);
    Application.m_asservissement.kp_distance = val;
    return true;
}

// _________________________________________________
bool CDebugSerial::action_set_Ki_distance(double val)
{
    _printf("Changement de la valeur du paramètre ki_distance: %f\n\r", val);
    Application.m_asservissement.ki_distance = val;
    return true;
}

// _________________________________________________
bool CDebugSerial::action_set_Kp_angle(double val)
{
    _printf("Changement de la valeur du paramètre kp_angle: %f\n\r", val);
    Application.m_asservissement.kp_angle = val;
    return true;
}

// _________________________________________________
bool CDebugSerial::action_set_Ki_angle(double val)
{
    _printf("Changement de la valeur du paramètre ki_angle: %f\n\r", val);
    Application.m_asservissement.ki_angle = val;
    return true;
}

// _________________________________________________
bool CDebugSerial::affiche_codeurs()
{
    _printf("CodeurG =%d / CodeurD=%d\n\r", Application.m_codeurs.read_CodeurGauche(),
                                            Application.m_codeurs.read_CodeurDroit());
    _printf("Codeur3 =%d / Codeur4=%d\n\r", Application.m_codeurs.read_Codeur3(),
                                            Application.m_codeurs.read_Codeur4());
    return true;
}

// _________________________________________________
bool CDebugSerial::raz_codeurs()
{
    Application.m_codeurs.reset_codeurs_G_D();
    affiche_codeurs();
    return true;
}

// _________________________________________________
// Fonction appelée à chaque fois qu'un octet arrive sur la RS232
void CDebugSerial::analyze(char c)
{
    receive_car(c);
}

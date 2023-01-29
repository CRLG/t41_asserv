#ifndef DEBUG_SERIAL_H
#define DEBUG_SERIAL_H

#include "console_interaction.h"

class CDebugSerial : public ConsoleInteraction
{
public:
    CDebugSerial();

    /*virtual*/ void send_to_console(char msg[]);   // Fonction à implémenter par la classe héritée pour faire le lien avec le hardware (envoie d'une chaine de caractèrevers la console)

    void analyze(char c);
    
    // Pages
    void page_principale();
    void page_commande_moteurs();
    void page_commande_mouvements();
    void page_reglage_coefs();
    void page_data_logger();
    void page_codeurs();

    void page_kp_distance();
    void page_ki_distance();
    void page_kp_angle();
    void page_ki_angle();

    // Actions
    bool arret_moteurs();
    bool cde_mot_G_M1();
    bool cde_mot_G_M2();
    bool cde_mot_G_M3();
    bool cde_mot_G_P1();
    bool cde_mot_G_P2();
    bool cde_mot_G_P3();

    bool cde_mot_D_M1();
    bool cde_mot_D_M2();
    bool cde_mot_D_M3();
    bool cde_mot_D_P1();
    bool cde_mot_D_P2();
    bool cde_mot_D_P3();

    bool cde_mot_GD_M1();
    bool cde_mot_GD_M2();
    bool cde_mot_GD_M3();
    bool cde_mot_GD_P1();
    bool cde_mot_GD_P2();
    bool cde_mot_GD_P3();

    bool force_asserv_manuel();
    bool cde_distance1();
    bool cde_distance2();
    bool cde_distance3();
    bool cde_distance4();
    bool cde_angle1();
    bool cde_angle2();
    bool cde_angle3();
    bool cde_angle4();
    bool cde_angle5();
    bool cde_angle6();

    bool start_logger();
    bool stop_logger();
    bool print_logger();
    bool synchro_logger_off();
    bool synchro_logger_on();

    bool affiche_coefs_asserv();
    bool action_set_Kp_distance(double val);
    bool action_set_Ki_distance(double val);
    bool action_set_Kp_angle(double val);
    bool action_set_Ki_angle(double val);

    bool affiche_codeurs();
    bool raz_codeurs();

    void affiche_menu();

    bool m_synchro_logger;
};

#endif // DEBUG_SERIAL_H

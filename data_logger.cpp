#include "data_logger.h"

#include "CGlobale.h"

// Exploitation des résultats :
// Dans gtkterm :
//   Démarrer la capture dans un fichier log.csv par exemple et s'assurer que le fichier est vide
//
// Sur la teensy, lancer l'affichage des logs par la touche 'p' dans le menu "Data Logger"

// Une fois le fichier présent sur le disque dur, l'ouvrir avec Libre Office Calc
// Supprimer les premières lignes qui peuvent être des restes des derniers affichage console
// Remplacer les "." par des "," pour que les valeurs soient considérées comme des valeurs numériques


// TODO : introduire la notion de rollback pour recommencer l'écriture à l'index "0" en cas de débordement
// et assurer ainsi l'enregistrement des X dernières secondes
// La première colonne étant l'heure, il suffira dans Excel de trier par ordre croissant pour remttre tout dans le bon ordre avant d'exploiter

// Pour pouvoir utiliser la 2ème zone RAM (large buffer), la structure et le buffer ne sont pas
// déclarés dans la classe
typedef struct
{
    long _time;
    int codeur_g;
    int codeur_d;
    float x_pos;
    float y_pos;
    float teta_pos;
    float erreur_distance;
    float erreur_angle;
    float cde_moteur_g;
    float cde_moteur_d;
    float vitesse_avance_robot;
    float vitesse_rotation_robot;
    int compteur_diag_blocage;
    char diag_blocage;
    char convergence_rapide;
    char convergence_conf;

}tLogData;

static const int NBRE_LIGNES = 8000;
// Le mot clé "DMAMEM" permet d'utiliser le 2ème buffer RAM
DMAMEM static tLogData m_datas[NBRE_LIGNES];


CDataLogger::CDataLogger()
    : m_started(false),
      m_start_time(0),
      m_index(0)
{
}

// ________________________________________
/*! Démarre le logger
 */
void CDataLogger::start()
{
    m_index = 0;
    m_started = true;
}

// ________________________________________
/*! Arrêt le logger
 */
void CDataLogger::stop()
{
    m_started = false;
}

// ________________________________________
/*! Log un pas
 * return true si l'enregistrement a pu être fait / false en cas de buffer plein
 */
bool CDataLogger::step()
{
    if (!m_started)             return false;
    if (m_index >= NBRE_LIGNES) return false;

    m_datas[m_index]._time = millis();
    m_datas[m_index].codeur_g =                 Application.m_codeurs.read_CodeurGauche();
    m_datas[m_index].codeur_d =                 Application.m_codeurs.read_CodeurDroit();
    m_datas[m_index].x_pos =                    Application.m_asservissement.X_robot;
    m_datas[m_index].y_pos =                    Application.m_asservissement.Y_robot;
    m_datas[m_index].teta_pos =                 Application.m_asservissement.angle_robot;
    m_datas[m_index].erreur_distance =          Application.m_asservissement.erreur_distance;
    m_datas[m_index].erreur_angle =             Application.m_asservissement.erreur_angle;
    m_datas[m_index].cde_moteur_g =             Application.m_asservissement.cde_moteur_G;
    m_datas[m_index].cde_moteur_d =             Application.m_asservissement.cde_moteur_D;
    m_datas[m_index].vitesse_avance_robot =     Application.m_asservissement.vitesse_avance_robot;
    m_datas[m_index].vitesse_rotation_robot =   Application.m_asservissement.vitesse_rotation_robot;
    m_datas[m_index].compteur_diag_blocage =    Application.m_asservissement.compteur_diag_blocage;
    m_datas[m_index].diag_blocage =             Application.m_asservissement.diag_blocage;
    m_datas[m_index].convergence_rapide =       Application.m_asservissement.convergence_rapide;
    m_datas[m_index].convergence_conf =         Application.m_asservissement.convergence_conf;

    m_index++;
    return true;
}


// ________________________________________
/*! Affiche dans la console le log complet au format csv
 */
void CDataLogger::print()
{

    Serial.printf("Time; codeur_g; codeur_d; x_pos; y_pos; teta_pos; erreur_distance; erreur_angle; cde_moteur_g; cde_moteur_d; vitesse_avance_robot; vitesse_rotation_robot; compteur_diag_blocage; diag_blocage; convergence_rapide; convergence_conf");
    Serial.printf("\n\r");
    for (long i=0; i<m_index; i++)
    {
        Serial.printf("%d;", m_datas[i]._time);
        Serial.printf("%d;", m_datas[i].codeur_d);
        Serial.printf("%d;", m_datas[i].codeur_g);
        Serial.printf("%f;", m_datas[i].x_pos);
        Serial.printf("%f;", m_datas[i].y_pos);
        Serial.printf("%f;", m_datas[i].teta_pos);
        Serial.printf("%f;", m_datas[i].erreur_distance);
        Serial.printf("%f;", m_datas[i].erreur_angle);
        Serial.printf("%f;", m_datas[i].cde_moteur_g);
        Serial.printf("%f;", m_datas[i].cde_moteur_d);
        Serial.printf("%f;", m_datas[i].vitesse_avance_robot);
        Serial.printf("%f;", m_datas[i].vitesse_rotation_robot);
        Serial.printf("%d;", m_datas[i].compteur_diag_blocage);
        Serial.printf("%d;", m_datas[i].diag_blocage);
        Serial.printf("%d;", m_datas[i].convergence_rapide);
        Serial.printf("%d", m_datas[i].convergence_conf);

        // ...
        Serial.printf("\n\r");
    }
    Serial.printf("\n\r");
}


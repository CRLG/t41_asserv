#include <FlexiTimer2.h>
#include "application.h"
#include <Servo.h>
#include "TeensyID.h"
#include "InternalTemperature.h"
#include "EEPROM.h"
#include "FreqMeasure.h"

extern "C" uint32_t set_arm_clock(uint32_t frequency); // required prototype

CApplication::CApplication()
{
}

static boolean tick = 0;
void flash()
{
    tick = 1;
}


//___________________________________________________________________________
void CApplication::init(void)
{
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(PIN_LED1, OUTPUT);
    pinMode(PIN_LED2, OUTPUT);
    pinMode(PIN_LED3, OUTPUT);

    analogWriteFrequency(PIN_Mot1_PWM, 20000);  // PWM de commande moteur à 20kHz
    analogWriteFrequency(PIN_Mot2_PWM, 20000);
    analogWriteFrequency(PIN_Mot3_PWM, 20000);
    analogWriteResolution(10);  // 1024 pas de PWM
    pinMode(PIN_Mot1_PWM, OUTPUT);
    pinMode(PIN_Mot1_PWM, OUTPUT);
    pinMode(PIN_Mot1_PWM, OUTPUT);
    pinMode(PIN_Mot1_Sens1, OUTPUT);
    pinMode(PIN_Mot1_Sens2, OUTPUT);
    pinMode(PIN_Mot2_Sens1, OUTPUT);
    pinMode(PIN_Mot2_Sens2, OUTPUT);

    FlexiTimer2::set(PERIODE_TICK, 1.0/1000, flash); // call every 10ms "ticks"
    FlexiTimer2::start();

    //m_moteurs.init();
    m_codeurs.init();
    //m_debug_serial.affiche_menu();

    // Changement dynamique de la fréquence d'horloge
    // (peut être changée en live en plein milieu d'exécution du programme)
    // Possibilité d'ajuster la fréquence en fonction de la température du CPU
    const int CPU_freq_MHz = 150;
    set_arm_clock(CPU_freq_MHz*1000000);

    // Ecriture en EEPROM
    /*
  EEPROM.update(0, 0x69);
  EEPROM.update(1, 0xA5);
  EEPROM.update(2, 0x96);
  EEPROM.update(3, 0x5A);
*/  

    m_messenger_asserv_deporte.initI2C();
}


//___________________________________________________________________________
void CApplication::run(void)
{
    if (tick==1)
    {
        tick = 0;
        Sequenceur();
    }

    while(Serial.available() > 0) {
        char incomingByte = Serial.read();
        m_debug_serial.analyze(incomingByte);
    }

    // TODO :
    // Mettre ici la RS232 n°1 ou n°2 pour pilotage du messenger via RS232 en parallèle de l'I2C

    // I2C
    m_messenger_asserv_deporte.checkI2CReceive();
}

//___________________________________________________________________________
/*!
   \brief Sequenceur de taches

   \param --
   \return --
*/
void CApplication::Sequenceur(void)
{
    static unsigned int cpt1msec = 0;
    static unsigned int cpt5msec = 0;
    static unsigned int cpt10msec = 0;
    static unsigned int cpt20msec = 0;
    static unsigned int cpt50msec = 0;
    static unsigned int cpt100msec = 0;
    static unsigned int cpt200msec = 0;
    static unsigned int cpt500msec = 0;
    static unsigned int cpt1sec = 0;
    static bool led1= false;
    static bool led2 = false;
    static bool led3 = false;
    static bool led_in = false;

    // ______________________________
    cpt1msec++;
    if (cpt1msec >= TEMPO_1msec) {
        cpt1msec = 0;
        m_asservissement.CalculsMouvementsRobots();
        m_data_logger.step();
    }

    // ______________________________
    cpt5msec++;
    if (cpt5msec >= TEMPO_5msec) {
        cpt5msec = 0;
    }
    // ______________________________
    cpt10msec++;
    if (cpt10msec >= TEMPO_10msec) {
        cpt10msec = 0;
    }

    // ______________________________
    cpt20msec++;
    if (cpt20msec >= TEMPO_20msec) {
        cpt20msec = 0;

        digitalWrite(LED_BUILTIN, led_in);
        led_in = ! led_in;
    }

    // ______________________________
    cpt50msec++;
    if (cpt50msec >= TEMPO_50msec) {
        cpt50msec = 0;
    }

    // ______________________________
    cpt100msec++;
    if (cpt100msec >= TEMPO_100msec) {
        cpt100msec = 0;
    }

    // ______________________________
    cpt200msec++;
    if (cpt200msec >= TEMPO_200msec) {
        cpt200msec = 0;
        digitalWrite(PIN_LED3, led3);
        led3 = ! led3;
    }
    // ______________________________
    cpt500msec++;
    if (cpt500msec >= TEMPO_500msec) {
        cpt500msec = 0;

        digitalWrite(PIN_LED2, led2);
        led2 = ! led2;
    }
    // ______________________________
    cpt1sec++;
    if (cpt1sec >= TEMPO_1sec) {
        cpt1sec = 0;
     }
}

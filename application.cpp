#include <FlexiTimer2.h>
#include "application.h"
#include <Servo.h>
#include "TeensyID.h"
#include "InternalTemperature.h"
#include "EEPROM.h"
#include "FreqMeasure.h"

#include <imx_rt1060_i2c_driver.h>
#include <i2c_driver.h>
#include <i2c_driver_wire.h>

// I2C
const uint8_t slave_address = 0x4D; // à vériier : adresse I2C 7 ou 8 bits ?
I2CSlave& slave = Slave;
void after_receive(size_t length, uint16_t address);
void before_transmit(uint16_t address);

// Double receive buffers to hold data from master.
const size_t slave_rx_buffer_size = 4;
uint8_t slave_rx_buffer[slave_rx_buffer_size] = {};
uint8_t slave_rx_buffer_2[slave_rx_buffer_size] = {};
volatile size_t slave_bytes_received = 0;

const size_t slave_tx_buffer_size = 32;
uint8_t slave_tx_buffer[slave_tx_buffer_size] = {};

void log_message_received();


extern "C" uint32_t set_arm_clock(uint32_t frequency); // required prototype


// I2C
// Called by the I2C interrupt service routine.
// This method must be as fast as possible.
// Do not perform IO in it.
void after_receive(size_t length, uint16_t address) {
    Serial.printf("after_receive : len=%d\n\r", length);
    // This is the only time we can guarantee that the
    // receive buffer is not changing.
    // Copy the content so we can handle it in the main loop.
    if (!slave_bytes_received) {
        memcpy(slave_rx_buffer_2, slave_rx_buffer, length);
        slave_bytes_received = length;
    }
    // else ignore this message because the main loop hasn't
    // handled the previous one yet.
}

void log_message_received() {
    if (slave.has_error()) {
        if (slave.error() == I2CError::buffer_overflow) {
            Serial.println("App: Buffer Overflow. (Master sent too many bytes.)");
        } else {
            Serial.println("App: Unexpected error");
        }
    }
    Serial.print("App: Slave received ");
    Serial.print(slave_bytes_received);
    Serial.print(" bytes: ");
    for(size_t i=0; i<slave_bytes_received; i++) {
        Serial.print(slave_rx_buffer_2[i]);
        Serial.print(", ");
    }
    Serial.println();
}


void before_transmit(uint16_t address)
{
    Serial.printf("before_transmit");

    int i=0;
    //slave_tx_buffer[i++]++;
    //slave_tx_buffer[i++]++;
    slave_tx_buffer[i++] = 0xBC;
    slave_tx_buffer[i++] = 0xDE;
    slave_tx_buffer[i++] = 0xFF;

/*
    slave_tx_buffer[i++] = 0x12;
    slave_tx_buffer[i++] = 0x34;
    slave_tx_buffer[i++] = 0x56;
    slave_tx_buffer[i++] = 0x78;
    slave_tx_buffer[i++] = 0x9A;
    slave_tx_buffer[i++] = 0xBC;
    slave_tx_buffer[i++] = 0xDE;
    slave_tx_buffer[i++] = 0xFF;
*/
}


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

    // Configure I2C Slave
     slave.after_receive(after_receive);
     slave.set_receive_buffer(slave_rx_buffer, slave_rx_buffer_size);

     slave.before_transmit(before_transmit);
     slave.set_transmit_buffer(slave_tx_buffer, slave_tx_buffer_size);

     // Enable the slave
     slave.listen(slave_address);
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

    // I2C
    if (slave_bytes_received) {
        log_message_received();
        slave_bytes_received = 0;
    }
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

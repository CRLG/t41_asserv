#include "MessengerAsservissementDeporte.h"
#include "messagebase.h"
#include "CGlobale.h"

#include <imx_rt1060_i2c_driver.h>
#include <i2c_driver.h>
#include <i2c_driver_wire.h>

// I2C
const uint8_t ADDRESS_I2C_SLAVE_TEENSY_ASSERV_DEPORTE = 0x4D; // à vériier : adresse I2C 7 ou 8 bits ?
I2CSlave& slave = Slave;

// Double receive buffers to hold data from master.
const size_t SLAVE_RX_BUFFER_SIZE = 64;
uint8_t _slave_rx_buffer[SLAVE_RX_BUFFER_SIZE] = {};
uint8_t _slave_rx_buffer_2[SLAVE_RX_BUFFER_SIZE] = {};
volatile size_t _slave_bytes_received = 0;

const size_t SLAVE_TX_BUFFER_SIZE = 64;
uint8_t _slave_tx_buffer[SLAVE_TX_BUFFER_SIZE] = {};

// I2C
// Called by the I2C interrupt service routine.
// This method must be as fast as possible.
// Do not perform IO in it.
void after_receive(size_t length, uint16_t address)
{
    Serial.printf("after_receive : len=%d\n\r", length);
    // This is the only time we can guarantee that the
    // receive buffer is not changing.
    // Copy the content so we can handle it in the main loop.
    if (!_slave_bytes_received) {
        memcpy(_slave_rx_buffer_2, _slave_rx_buffer, length);
        _slave_bytes_received = length;
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
    Serial.print(_slave_bytes_received);
    Serial.print(" bytes: ");
    for(size_t i=0; i<_slave_bytes_received; i++) {
        Serial.print(_slave_rx_buffer_2[i]);
        Serial.print(", ");
    }
    Application.m_messenger_asserv_deporte.decode(_slave_rx_buffer, _slave_bytes_received);
    Serial.println();
}

void before_transmit(uint16_t address)
{
    (void)address;
    Serial.printf("before_transmit");

    /*
    // Pour les essais uniquement (à supprimer ensuite)
    Application.m_messenger_i2c.m_database.m_EtatAsservissement.X_robot = -1.2;
    Application.m_messenger_i2c.m_database.m_EtatAsservissement.Y_robot = 3.4;
    Application.m_messenger_i2c.m_database.m_EtatAsservissement.angle_robot = -3.17;
    Application.m_messenger_i2c.m_database.m_EtatAsservissement.convergence_rapide= 1;
    Application.m_messenger_i2c.m_database.m_EtatAsservissement.convergence_conf= 0;
    Application.m_messenger_i2c.m_database.m_EtatAsservissement.diag_blocage= 1;
    Application.m_messenger_i2c.m_database.m_EtatAsservissement.ModeAsservissement= 100;
    Application.m_messenger_i2c.m_database.m_EtatAsservissement.cde_moteur_D= 45;
    Application.m_messenger_i2c.m_database.m_EtatAsservissement.cde_moteur_G= 23;
    */
    Application.m_messenger_asserv_deporte.m_database.encode(&Application.m_messenger_asserv_deporte.m_database.m_EtatAsservissement);
}


MessengerAsservissementDeporte::MessengerAsservissementDeporte()
{
    init(&m_transporter, &m_database);
    initMessages();
    m_last_id_cde_asserv = 0;
}

MessengerAsservissementDeporte::~MessengerAsservissementDeporte()
{
}

// ______________________________________________
void MessengerAsservissementDeporte::initMessages()
{
    /*
    m_database.m_TimestampMatch.setDestinationAddress(0xFFFF);
    m_database.m_TimestampMatch.setTransmitPeriod(1000);

    m_database.m_GrosbotPosition.setDestinationAddress(0xFFFF);
    m_database.m_GrosbotPosition.setTransmitPeriod(2100);

    m_database.m_CommandeExperience.setDestinationAddress(0xFFFF);
    m_database.m_CommandeExperience.setTransmitPeriod(1020);
    */
}

// ______________________________________________
void MessengerAsservissementDeporte::initI2C()
{
    // Configure I2C Slave
     slave.after_receive(after_receive);
     slave.set_receive_buffer(_slave_rx_buffer, SLAVE_RX_BUFFER_SIZE);

     slave.before_transmit(before_transmit);
     slave.set_transmit_buffer(_slave_tx_buffer, SLAVE_TX_BUFFER_SIZE);

     // Enable the slave
     slave.listen(ADDRESS_I2C_SLAVE_TEENSY_ASSERV_DEPORTE);
}


// ______________________________________________
void MessengerAsservissementDeporte::checkI2CReceive()
{
    if (_slave_bytes_received) {
        log_message_received();
        _slave_bytes_received = 0;
    }
}

// ______________________________________________
void MessengerAsservissementDeporte::start()
{
    m_database.restart();
}

// ______________________________________________
void MessengerAsservissementDeporte::stop()
{
}

// ______________________________________________
void MessengerAsservissementDeporte::execute()
{
    // TODO ?

    m_database.checkAndSendPeriodicMessages();
    m_database.checkNodeCommunication();
}

// ===================================================
//              MESSENGER OUTPUT
// ===================================================
// ______________________________________________
// Fonction appelée par le Transporter pour envoyer les octets du message encodé
void MessengerAsservissementDeporte::encode(unsigned char *buff_data, unsigned short buff_size, unsigned short dest_address)
{
    (void)dest_address;
    // Met à jour le buffer de transmission qui sera envoyé au moment de la communication sur l'I2C
    memcpy(_slave_tx_buffer, buff_data, buff_size);
    Serial.printf("MessengerAsservissementDeporte::encode : %d bytes\n\r", buff_size);
}

// ===================================================
//              MESSENGER RESSOURCES
// ===================================================
// ______________________________________________
long MessengerAsservissementDeporte::getTime()
{
    return millis();
}

// ===================================================
//                  MESSENGER EVENTS
// ===================================================
// ______________________________________________
void MessengerAsservissementDeporte::newFrameReceived(tMessengerFrame *frame)
{
    (void)frame;
}

// ______________________________________________
void MessengerAsservissementDeporte::newMessageReceived(MessageBase *msg)
{
    printf("MessengerAsservissementDeporte::newMessageReceived : 0x%x", msg->getID());
    unsigned short msg_id = msg->getID();
    if (msg_id == m_database.m_CommandeMouvementXY.getID()) {
        m_last_id_cde_asserv = m_database.m_CommandeMouvementXY.id;
        float x = m_database.m_CommandeMouvementXY.x;
        float y = m_database.m_CommandeMouvementXY.y;
        Serial.printf("Message CommandeMouvementXY(%f, %f) - ID=%d\r\n", x, y, m_last_id_cde_asserv);
        Application.m_asservissement.CommandeMouvementXY(x, y);
    }
    else if (msg_id == m_database.m_CommandeMouvementXYTeta.getID()) {
        m_last_id_cde_asserv = m_database.m_CommandeMouvementXYTeta.id;
        float x = m_database.m_CommandeMouvementXYTeta.x;
        float y = m_database.m_CommandeMouvementXYTeta.y;
        float teta = m_database.m_CommandeMouvementXYTeta.teta;
        Serial.printf("Message CommandeMouvementXY_Teta(%f, %f) - ID=%d\r\n", x, y, m_last_id_cde_asserv);
        Application.m_asservissement.CommandeMouvementXY_TETA(x, y, teta);
    }
    else if (msg_id == m_database.m_CommandeMouvementXY_A.getID()) {
        m_last_id_cde_asserv = m_database.m_CommandeMouvementXY_A.id;
        float x = m_database.m_CommandeMouvementXY_A.x;
        float y = m_database.m_CommandeMouvementXY_A.y;
        Serial.printf("Message CommandeMouvementXY_A(%f, %f) - ID=%d\r\n", x, y, m_last_id_cde_asserv);
        Application.m_asservissement.CommandeMouvementXY_A(x, y);
    }
    else if (msg_id == m_database.m_CommandeMouvementXY_B.getID()) {
        m_last_id_cde_asserv = m_database.m_CommandeMouvementXY_B.id;
        float x = m_database.m_CommandeMouvementXY_B.x;
        float y = m_database.m_CommandeMouvementXY_B.y;
        Serial.printf("Message CommandeMouvementXY_B(%f, %f) - ID=%d\r\n", x, y, m_last_id_cde_asserv);
        Application.m_asservissement.CommandeMouvementXY_B(x, y);
    }
    else if (msg_id == m_database.m_CommandeMouvementDistanceAngle.getID()) {
        m_last_id_cde_asserv = m_database.m_CommandeMouvementDistanceAngle.id;
        float distance = m_database.m_CommandeMouvementDistanceAngle.distance;
        float angle = m_database.m_CommandeMouvementDistanceAngle.angle;
        Serial.printf("Message CommandeMouvementDistanceAngle(%f, %f) - ID=%d\r\n", distance, angle, m_last_id_cde_asserv);
        Application.m_asservissement.CommandeMouvementDistanceAngle(distance, angle);
    }
    else if (msg_id == m_database.m_CommandeVitesseMouvement.getID()) {
        m_last_id_cde_asserv = m_database.m_CommandeVitesseMouvement.id;
        float vitesse_avance = m_database.m_CommandeVitesseMouvement.vitesse_avance;
        float vitesse_angle = m_database.m_CommandeVitesseMouvement.vitesse_angle;
        Serial.printf("Message CommandeVitesseMouvement(%f, %f) - ID=%d\r\n", vitesse_avance, vitesse_angle, m_last_id_cde_asserv);
        Application.m_asservissement.CommandeVitesseMouvement(vitesse_avance, vitesse_angle);
    }

    // else if .... tester tous les messages possibles
}

// ______________________________________________
void MessengerAsservissementDeporte::frameTransmited(tMessengerFrame *frame)
{
    (void)frame;
}

// ______________________________________________
void MessengerAsservissementDeporte::messageTransmited(MessageBase *msg)
{
    (void)msg;
}

// ______________________________________________
void MessengerAsservissementDeporte::dataUpdated(char *name, char *val_str)
{
    (void)name;
    (void)val_str;
}

// ______________________________________________
void MessengerAsservissementDeporte::dataChanged(char *name, char *val_str)
{
    (void)name;
    (void)val_str;
}

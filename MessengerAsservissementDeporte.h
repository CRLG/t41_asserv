#ifndef _ASSERVISSEMENT_DEPORTE_MESSENGER_H_
#define _ASSERVISSEMENT_DEPORTE_MESSENGER_H_

#include <cstdint>
#include <cstddef>
#include <functional>

#include "databaseasservissementdeporte.h"
#include "transportergeneric.h"
#include "messengerinterfacebase.h"


// ====================================================
//
// ====================================================
class MessengerAsservissementDeporte : public MessengerInterfaceBase
{
public:
    MessengerAsservissementDeporte();
    virtual ~MessengerAsservissementDeporte();

    void start();
    void stop();
    void execute();

    void initI2C();
    void checkI2CReceive();

    // =============================================
    //    Reimplement MessengerInterfaceBase virual
    virtual void encode(unsigned char *buff_data, unsigned short buff_size, unsigned short dest_address=0);

    // This method is called by messenger to get current time [msec]
    virtual long getTime();

    // Events
    // This method is called by messenger (transporter) to inform a valid frame was received
    virtual void newFrameReceived(tMessengerFrame *frame);
    // This method is called by messenger (transporter) to inform a frame was transmited
    virtual void frameTransmited(tMessengerFrame *frame);
    // This method is called by messenger (database) to inform a known message was received
    virtual void newMessageReceived(MessageBase *msg);
    // This method is called by messenger (database) to inform a message was transmited
    virtual void messageTransmited(MessageBase *msg);
    // This method is called by messenger (message) to inform a data in a message was updated
    virtual void dataUpdated(char *name, char *val_str);
    // This method is called by messenger (message) to inform a data in a message changed value
    virtual void dataChanged(char *name, char *val_str);

    DatabaseAsservissementDeporte m_database;
    TransporterGeneric m_transporter;


private :
    unsigned short m_last_id_cde_asserv;
    void initMessages();
};

#endif // _ASSERVISSEMENT_DEPORTE_MESSENGER_H_

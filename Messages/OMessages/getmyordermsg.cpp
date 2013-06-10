#include "getmyordermsg.h"

GetMyOrderMsg::GetMyOrderMsg() : OMessage()
{   }

IOMessage::MessageType GetMyOrderMsg::type() const
{
    return GET_MY_ORDERS;
}

void GetMyOrderMsg::send(QIODevice* connection)
{
    // Domyślnie BigEndian
    QDataStream out(connection);

    sendHeader(out);
}

qint16 GetMyOrderMsg::length() const
{
    return sizeof(IOMessage::MessageType);
}


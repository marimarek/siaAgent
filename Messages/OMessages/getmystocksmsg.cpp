#include "getmystocksmsg.h"

GetMyStocksMsg::GetMyStocksMsg() : OMessage()
{
}

IOMessage::MessageType GetMyStocksMsg::type() const
{
    return GET_MY_STOCKS;
}

void GetMyStocksMsg::send(QIODevice* connection)
{
    // Domyślnie BigEndian
    QDataStream out(connection);

    sendHeader(out);
}

qint16 GetMyStocksMsg::length() const
{
    return sizeof(IOMessage::MessageType);
}

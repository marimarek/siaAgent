#include "subscribestockmsg.h"

SubscribeStockMsg::SubscribeStockMsg(qint32 stockId) : OMessage(), m_stockId(stockId)
{   }

IOMessage::MessageType SubscribeStockMsg::type() const
{
    return SUBSCRIBE_STOCK;
}

void SubscribeStockMsg::send(QIODevice* connection)
{
    // Domyślnie BigEndian
    QDataStream out(connection);

    sendHeader(out);
    out << static_cast<qint32>(m_stockId);
}

qint16 SubscribeStockMsg::length() const
{
    return sizeof(IOMessage::MessageType) + sizeof(m_stockId);
}

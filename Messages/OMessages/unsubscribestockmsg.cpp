#include "unsubscribestockmsg.h"


UnsubscribeStockMsg::UnsubscribeStockMsg(qint32 stockId) : m_stockId(stockId)
{   }

IOMessage::MessageType UnsubscribeStockMsg::type() const
{
    return UNSUBSCRIBE_STOCK;
}

void UnsubscribeStockMsg::send(QIODevice* connection)
{
    // Domyślnie BigEndian
    QDataStream out(connection);

    sendHeader(out);
    out << static_cast<qint32>(m_stockId);
}

qint16 UnsubscribeStockMsg::length() const
{
    return sizeof(IOMessage::MessageType) + sizeof(m_stockId);
}

#include "getstockinfomsg.h"

GetStockInfoMsg::GetStockInfoMsg(qint32 stockId) : OMessage(), m_stockId(stockId)
{   }

IOMessage::MessageType GetStockInfoMsg::type() const
{
    return GET_STOCK_INFO;
}

void GetStockInfoMsg::send(QIODevice* connection)
{
    // Domyślnie BigEndian
    QDataStream out(connection);

    sendHeader(out);
    out << static_cast<qint32>(m_stockId);
}

qint16 GetStockInfoMsg::length() const
{
    return sizeof(IOMessage::MessageType) + sizeof(m_stockId);
}

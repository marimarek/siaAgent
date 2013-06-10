#include "sellstockreqmsg.h"


SellStockReqMsg::SellStockReqMsg(qint32 stockId, qint32 amount, qint32 price)
    : OMessage(), m_stockId(stockId), m_amount(amount), m_price(price)
{   }

IOMessage::MessageType SellStockReqMsg::type() const
{
    return SELL_STOCK_REQ;
}


void SellStockReqMsg::send(QIODevice* connection)
{
    // Domyślnie BigEndian
    QDataStream out(connection);

    sendHeader(out);
    out << static_cast<qint32>(m_stockId)
        << static_cast<qint32>(m_amount)
        << static_cast<qint32>(m_price);
}

qint16 SellStockReqMsg::length() const
{
    return sizeof(IOMessage::MessageType) + sizeof(m_stockId) + sizeof(m_amount) + sizeof(m_price);
}

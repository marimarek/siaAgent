#include "buystockreqmsg.h"


BuyStockReqMsg::BuyStockReqMsg(qint32 stockId, qint32 amount, qint32 price)
    : OMessage(), m_stockId(stockId), m_amount(amount), m_price(price)
{   }

IOMessage::MessageType BuyStockReqMsg::type() const
{
    return BUY_STOCK_REQ;
}

void BuyStockReqMsg::send(QIODevice* connection)
{
    // Domyślnie BigEndian
    QDataStream out(connection);

    sendHeader(out);
    out << static_cast<qint32>(m_stockId)
        << static_cast<qint32>(m_amount)
        << static_cast<qint32>(m_price);

}

qint16 BuyStockReqMsg::length() const
{
    return sizeof(IOMessage::MessageType) + sizeof(m_stockId) + sizeof(m_amount) + sizeof(m_price);
}

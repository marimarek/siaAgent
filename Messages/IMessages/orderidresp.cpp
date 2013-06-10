#include "orderidresp.h"

OrderIdResp::OrderIdResp(QDataStream& in) : IMessage(in)
{
    in >> m_orderId;
}

IOMessage::MessageType OrderIdResp::type() const
{
    return ORDER_ID_RESP;
}

qint32 OrderIdResp::getOrderId()
{
    return m_orderId;
}

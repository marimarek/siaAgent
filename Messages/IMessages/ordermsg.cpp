#include "ordermsg.h"
OrderMsg::OrderMsg(QDataStream &in) : IMessage(in)
{
    in >> m_order;
}

IOMessage::MessageType OrderMsg::type() const
{
    return ORDER;
}

Order::OrderType OrderMsg::getTransactionType()
{
    return m_order.getTransactionType();
}

qint32 OrderMsg::getStockId()
{
    return m_order.getStockId();
}

qint32 OrderMsg::getAmount()
{
   return m_order.getAmount();
}

qint32 OrderMsg::getPrice()
{
    return m_order.getPrice();
}

Order OrderMsg::getOrder()
{
    return m_order;
}

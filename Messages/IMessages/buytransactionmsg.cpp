#include "buytransactionmsg.h"
#include <QDataStream>

BuyTransactionMsg::BuyTransactionMsg(QDataStream &in) : IMessage(in)
{
    in >> m_orderId
       >> m_amount;
}

IOMessage::MessageType BuyTransactionMsg::type() const
{
    return BUY_TRANSACTION;
}

qint32 BuyTransactionMsg::getOrderId()
{
    return m_orderId;
}

qint32 BuyTransactionMsg::getAmount()
{
    return m_amount;
}

#include "selltransactionmsg.h"

SellTransactionMsg::SellTransactionMsg(QDataStream &in) : IMessage(in)
{
    in >> m_orderId
       >> m_amount;
}

IOMessage::MessageType SellTransactionMsg::type() const
{
    return SELL_TRANSACTION;
}

qint32 SellTransactionMsg::getOrderId()
{
    return m_orderId;
}

qint32 SellTransactionMsg::getAmount()
{
    return m_amount;
}

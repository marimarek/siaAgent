#ifndef SELLTRANSACTIONMSG_H
#define SELLTRANSACTIONMSG_H

#include "imessage.h"

class SellTransactionMsg : public IMessage
{
    qint32 m_orderId;
    qint32 m_amount;
public:
    SellTransactionMsg(QDataStream& in);

    MessageType type() const;
    qint32 getOrderId();
    qint32 getAmount();
};

#endif // SELLTRANSACTIONMSG_H

#ifndef BUYTRANSACTIONMSG_H
#define BUYTRANSACTIONMSG_H

#include "imessage.h"

class BuyTransactionMsg : public IMessage
{
    qint32 m_orderId;
    qint32 m_amount;
public:
    BuyTransactionMsg(QDataStream& in);

    MessageType type() const;
    qint32 getOrderId();
    qint32 getAmount();
};


#endif // BUYTRANSACTIONMSG_H

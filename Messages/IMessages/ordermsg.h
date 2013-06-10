#ifndef NEWTRANSACTION_H
#define NEWTRANSACTION_H

#include "imessage.h"
#include "order.h"

class OrderMsg : public IMessage
{
    Order m_order;
public:
    OrderMsg(QDataStream& in);

    IOMessage::MessageType type() const;
    Order::OrderType getTransactionType();
    qint32 getStockId();
    qint32 getAmount();
    qint32 getPrice();
    Order getOrder();

};

#endif // NEWTRANSACTION_H

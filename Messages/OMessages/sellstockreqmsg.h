#ifndef SELLSTOCKREQMSG_H
#define SELLSTOCKREQMSG_H

#include "omessage.h"

class SellStockReqMsg : public OMessage
{
    qint32 m_stockId;
    qint32 m_amount;
    qint32 m_price;

    qint16 length() const;
public:
    SellStockReqMsg(qint32 stockId, qint32 amount, qint32 price);

    MessageType type() const;
    void send(QIODevice* connection);
};

#endif // SELLSTOCKREQMSG_H

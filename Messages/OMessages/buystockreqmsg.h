#ifndef BUYSTOCKREQMSG_H
#define BUYSTOCKREQMSG_H

#include "omessage.h"


class BuyStockReqMsg : public OMessage
{
    qint32 m_stockId;
    qint32 m_amount;
    qint32 m_price;

    qint16 length() const;
public:
    BuyStockReqMsg(qint32 stockId, qint32 amount, qint32 price);

    MessageType type() const;
    void send(QIODevice* connection);
};

#endif // BUYSTOCKREQMSG_H

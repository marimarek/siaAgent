#ifndef SUBSCRIBESTOCKMSG_H
#define SUBSCRIBESTOCKMSG_H

#include "omessage.h"

class SubscribeStockMsg : public OMessage
{
    qint32 m_stockId;

    qint16 length() const;
public:
    SubscribeStockMsg( qint32 stockId);

    MessageType type() const;
    void send(QIODevice* connection);
};

#endif // SUBSCRIBESTOCKMSG_H

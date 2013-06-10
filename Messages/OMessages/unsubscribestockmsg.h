#ifndef UNSUBSCRIBESTOCKMSG_H
#define UNSUBSCRIBESTOCKMSG_H

#include "omessage.h"

#include <QDataStream>


class UnsubscribeStockMsg : public OMessage
{
    qint32 m_stockId;

    qint16 length() const;
public:
    UnsubscribeStockMsg(qint32 stockId);

    MessageType type() const;
    void send(QIODevice* connection);
};

#endif // UNSUBSCRIBESTOCKMSG_H

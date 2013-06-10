#ifndef CANCELORDERMSG_H
#define CANCELORDERMSG_H

#include "omessage.h"

class CancelOrderMsg : public OMessage
{
    qint32 m_orderId;

    qint16 length() const;
public:
    CancelOrderMsg(qint32 orderId);

    MessageType type() const;
    void send(QIODevice* connection);
};

#endif // CANCELORDERMSG_H

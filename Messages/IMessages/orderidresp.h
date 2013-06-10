#ifndef ORDERIDRESP_H
#define ORDERIDRESP_H

#include "imessage.h"

class OrderIdResp : public IMessage
{
    qint32 m_orderId;
public:
    OrderIdResp(QDataStream& in);

    IOMessage::MessageType type() const;
    qint32 getOrderId();
};

#endif // ORDERIDRESP_H

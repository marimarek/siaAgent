#ifndef GETSTOCKINFOMSG_H
#define GETSTOCKINFOMSG_H

#include <omessage.h>

class GetStockInfoMsg : public OMessage
{
    qint32 m_stockId;

    qint16 length() const;
public:
    GetStockInfoMsg(qint32 stockId);

    MessageType type() const;
    void send(QIODevice* connection);
};

#endif // GETSTOCKINFOMSG_H

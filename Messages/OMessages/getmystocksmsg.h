#ifndef GETMYSTOCKSMSG_H
#define GETMYSTOCKSMSG_H

#include "omessage.h"

class GetMyStocksMsg : public OMessage
{
    qint16 length() const;
public:
    GetMyStocksMsg();

    MessageType type() const;
    void send(QIODevice* connection);
};

#endif // GETMYSTOCKSMSG_H

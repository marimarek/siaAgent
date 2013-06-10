#ifndef GETMYORDERMSG_H
#define GETMYORDERMSG_H

#include "omessage.h"

class GetMyOrderMsg : public OMessage
{
    qint16 length() const;
public:
    GetMyOrderMsg();

    MessageType type() const;
    void send(QIODevice* connection);
};

#endif // GETMYORDERMSG_H

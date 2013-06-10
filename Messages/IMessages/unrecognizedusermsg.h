#ifndef UNRECOGNIZEDUSERMSG_H
#define UNRECOGNIZEDUSERMSG_H

#include "imessage.h"

class UnrecognizedUserMsg : public IMessage
{
public:
    UnrecognizedUserMsg(QDataStream& in);

    MessageType type() const;
};

#endif // UNRECOGNIZEDUSERMSG_H

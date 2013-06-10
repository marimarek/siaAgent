#ifndef BESTORDERMSG_H
#define BESTORDERMSG_H

#include "ordermsg.h"

class BestOrderMsg : public OrderMsg
{
public:
    BestOrderMsg(QDataStream& in);

    IOMessage::MessageType type() const;
};

#endif // BESTORDER_H

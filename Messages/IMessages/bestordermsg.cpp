#include "bestordermsg.h"

BestOrderMsg::BestOrderMsg(QDataStream& in) : OrderMsg(in)
{   }

IOMessage::MessageType BestOrderMsg::type() const
{
    return BEST_ORDER;
}

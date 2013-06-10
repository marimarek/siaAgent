#include "unrecognizedusermsg.h"

UnrecognizedUserMsg::UnrecognizedUserMsg(QDataStream &in) : IMessage(in)
{}

IOMessage::MessageType UnrecognizedUserMsg::type() const
{
    return UNRECOGNIZED_USER;
}

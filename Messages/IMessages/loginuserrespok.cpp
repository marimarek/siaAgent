#include "loginuserrespok.h"

#include <QDataStream>

LoginUserRespOk::LoginUserRespOk(QDataStream &in) : IMessage(in)
{
}
IOMessage::MessageType LoginUserRespOk::type() const
{
    return LOGIN_USER_RESP_OK;
}

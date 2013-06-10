#include "registeruserrespok.h"

RegisterUserRespOk::RegisterUserRespOk(QDataStream &in) : IMessage(in)
{
    in >> m_userId;
}

IOMessage::MessageType RegisterUserRespOk::type() const
{
    return REGISTER_USER_RESP_OK;
}

qint32 RegisterUserRespOk::getUserId() const
{
    return m_userId;
}

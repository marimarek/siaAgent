#include "registeruserreqmsg.h"

RegisterUserReqMsg::RegisterUserReqMsg(QString password) : OMessage(), m_password(password)
{   }

IOMessage::MessageType RegisterUserReqMsg::type() const
{
    return REGISTER_USER_REQ;
}

void RegisterUserReqMsg::send(QIODevice* connection)
{
    auto password = m_password.toUtf8();
    // Domyślnie BigEndian
    QDataStream out(connection);

    sendHeader(out);
    out << static_cast<qint16>(password.size());
    connection->write(password);
}

qint16 RegisterUserReqMsg::length() const
{
    return sizeof(IOMessage::MessageType) + sizeof(qint16) + m_password.size();
}

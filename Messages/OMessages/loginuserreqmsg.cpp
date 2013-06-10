#include "loginuserreqmsg.h"

LoginUserReqMsg::LoginUserReqMsg(qint32 userId, QString password)
    : OMessage(), m_userId(userId), m_password(password)
{   }

IOMessage::MessageType LoginUserReqMsg::type() const
{
    return LOGIN_USER_REQ;
}

void LoginUserReqMsg::send(QIODevice* connection)
{
    auto password = m_password.toUtf8();
    // Domyślnie BigEndian
    QDataStream out(connection);

    sendHeader(out);
    out << static_cast<qint32>(m_userId)
        << static_cast<qint16>(password.size());
    connection->write(password);
}

qint16 LoginUserReqMsg::length() const
{
    return sizeof(IOMessage::MessageType) + sizeof(m_userId) + sizeof(qint16) + m_password.size();
}

#include "loginuserrespfail.h"

#include <QDataStream>

LoginUserRespFail::LoginUserRespFail(QDataStream &in) : IMessage(in)
{
    qint16 reasonLength;
    in >> reasonLength;

    QByteArray buffer(reasonLength, Qt::Uninitialized);

    in.readRawData(buffer.data(), reasonLength);
    m_reason = QString(buffer);

}

IOMessage::MessageType LoginUserRespFail::type() const
{
    return LOGIN_USER_RESP_FAIL;
}

QString LoginUserRespFail::getReason()
{
    return m_reason;
}

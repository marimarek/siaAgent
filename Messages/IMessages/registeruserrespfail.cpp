#include "registeruserrespfail.h"

#include <QDataStream>


RegisterUserRespFail::RegisterUserRespFail(QDataStream &in) : IMessage(in)
{
    qint16 reasonLength;
    in >> reasonLength;

    QByteArray buffer(reasonLength, Qt::Uninitialized);

    in.readRawData(buffer.data(), reasonLength);
    m_reason = QString(buffer);
}

IOMessage::MessageType RegisterUserRespFail::type() const
{
    return REGISTER_USER_RESP_FAIL;
}

QString RegisterUserRespFail::getReason()
{
    return m_reason;
}

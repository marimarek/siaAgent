#ifndef REGISTERUSERRESPMSG_H
#define REGISTERUSERRESPMSG_H

#include "imessage.h"

#include <QIODevice>

class RegisterUserRespOk : public IMessage
{
    qint32 m_userId;
public:
    RegisterUserRespOk(QDataStream& in);

    MessageType type() const;
    qint32 getUserId() const;
};

#endif // REGISTERUSERRESPMSG_H

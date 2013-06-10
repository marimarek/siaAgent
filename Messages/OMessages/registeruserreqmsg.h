#ifndef REGISTERUSERREQMSG_H
#define REGISTERUSERREQMSG_H

#include "omessage.h"

#include <QString>

class RegisterUserReqMsg : public OMessage
{
    QString m_password;
    qint16 length() const;
public:
    RegisterUserReqMsg(QString password);

    MessageType type() const;
    void send(QIODevice* connection);
};

#endif // REGISTERUSERREQMSG_H

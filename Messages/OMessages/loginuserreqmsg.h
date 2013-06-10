#ifndef LOGINUSERMSG_H
#define LOGINUSERMSG_H

#include "omessage.h"

class LoginUserReqMsg : public OMessage
{
    qint32 m_userId;
    QString m_password;

    qint16 length() const;
public:
    LoginUserReqMsg(qint32 userId, QString password = "abcdef");

    MessageType type() const;
    void send(QIODevice* connection);

};

#endif // LOGINUSERMSG_H

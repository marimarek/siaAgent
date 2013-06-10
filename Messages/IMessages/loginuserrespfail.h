#ifndef LOGINUSERRESPFAIL_H
#define LOGINUSERRESPFAIL_H

#include "imessage.h"

#include <QString>

class LoginUserRespFail : public IMessage
{
    QString m_reason;
public:
    LoginUserRespFail(QDataStream& in);

    MessageType type() const;
    QString getReason();
};

#endif // LOGINUSERRESPFAIL_H

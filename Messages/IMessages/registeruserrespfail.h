#ifndef REGISTERUSERRESPFAIL_H
#define REGISTERUSERRESPFAIL_H

#include "imessage.h"

#include <QString>

class RegisterUserRespFail : public IMessage
{
    QString m_reason;
public:
    RegisterUserRespFail(QDataStream& in);

    MessageType type() const;
    QString getReason();
};


#endif // REGISTERUSERRESPFAIL_H

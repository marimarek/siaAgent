#ifndef LOGINUSERRESPOK_H
#define LOGINUSERRESPOK_H


#include "imessage.h"

class LoginUserRespOk : public IMessage
{
public:
    LoginUserRespOk(QDataStream& in);
    MessageType type() const;
};

#endif // LOGINUSERRESPOK_H

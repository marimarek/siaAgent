#ifndef IMESSAGE_H
#define IMESSAGE_H

#include "iomessage.h"

#include <QIODevice>
#include <QDataStream>

class IMessage : public IOMessage
{
public:
    static MessageType getMsgType(QIODevice *data);
    static bool isEnoughData(QIODevice* data);
protected:
    IMessage(QDataStream& in);

    static qint16 getMsgLength(QIODevice* data);
    void takeHeader(QDataStream& in);
};

#endif // IMESSAGE_H

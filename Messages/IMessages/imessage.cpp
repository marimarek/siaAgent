#include "imessage.h"

IMessage::IMessage(QDataStream& in) : IOMessage()
{
    takeHeader(in);
}

IOMessage::MessageType IMessage::getMsgType(QIODevice *data)
{
    qint16 msgLength;
    qint8 msgType;

    QDataStream in( data->peek(sizeof(msgLength) + sizeof(msgType)) );
    in >> msgLength;
    in >> msgType;
    return toType(msgType);
}

bool IMessage::isEnoughData(QIODevice* data)
{
    qint16 msgLength = getMsgLength(data);
    if(msgLength == -1)
        return false;
    return data->bytesAvailable() >= msgLength + sizeof(msgLength);

}

qint16 IMessage::getMsgLength(QIODevice* data)
{
    if(data->bytesAvailable() < 2)
        return -1;

    qint16 msgLength;

    QDataStream in(data->peek(2));
    in >> msgLength;

    return msgLength;
}

void IMessage::takeHeader(QDataStream& in)
{
    qint16 msgLength;
    qint8 msgType;

    in >> msgLength;
    in >> msgType;
}

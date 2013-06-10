#include "cancelordermsg.h"


CancelOrderMsg::CancelOrderMsg(qint32 orderId) : OMessage(), m_orderId(orderId)
{   }

IOMessage::MessageType CancelOrderMsg::type() const
{
    return CANCEL_ORDER_REQ;
}

void CancelOrderMsg::send(QIODevice* connection)
{
    // Domyślnie BigEndian
    QDataStream out(connection);

    sendHeader(out);
    out << static_cast<qint32>(m_orderId);

}

qint16 CancelOrderMsg::length() const
{
    return sizeof(IOMessage::MessageType) + sizeof(m_orderId);
}

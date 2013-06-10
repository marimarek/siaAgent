#ifndef GETMYORDERSRESPMSG_H
#define GETMYORDERSRESPMSG_H

#include "order.h"
#include "imessage.h"
#include <QVector>
#include <QPair>

class GetMyOrdersRespMsg : public IMessage
{
    QVector<QPair<qint32, Order> > m_orders;
public:
    GetMyOrdersRespMsg(QDataStream& in);

    MessageType type() const;
    qint32 numOfOrders();
    QPair<qint32, Order> operator[](int i);
    QVector<QPair<qint32, Order> > getOrders();
};

#endif // GETMYORDERSRESPMSG_H

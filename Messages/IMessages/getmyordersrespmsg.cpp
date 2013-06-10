#include "getmyordersrespmsg.h"

GetMyOrdersRespMsg::GetMyOrdersRespMsg(QDataStream& in) : IMessage(in)
{
    qint32 ordersLength;

    in >> ordersLength;
    m_orders.resize(ordersLength);

    for(int i = 0; i < ordersLength; ++i)
    {
        qint8 transactionType;
        qint32 stockId;
        qint32 amount;
        qint32 price;

        in >> transactionType
           >> m_orders[i].first
           >> stockId
           >> amount
           >> price;

        m_orders[i].second = Order(Order::toOrderType(transactionType), stockId, amount, price);
    }
}

IOMessage::MessageType GetMyOrdersRespMsg::type() const
{
    return GET_MY_ORDERS_RESP;
}

qint32 GetMyOrdersRespMsg::numOfOrders()
{
    return m_orders.size();
}

QPair<qint32, Order> GetMyOrdersRespMsg::operator[](int i)
{
    return m_orders[i];
}

QVector<QPair<qint32, Order> > GetMyOrdersRespMsg::getOrders()
{
    return m_orders;
}

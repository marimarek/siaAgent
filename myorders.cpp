#include "myorders.h"

MyOrders::MyOrders(): m_upToDate(false)
{   }

void MyOrders::setOrders(const QVector<QPair<qint32, Order> >& orders)
{
    m_notAssignedOrders.clear();
    clear();

    for(int i = 0; i < orders.size(); ++i)
        (*this)[orders[i].first] = orders[i].second;

    m_upToDate = true;
}

void MyOrders::pushOrder(const Order& order)
{
    m_notAssignedOrders.enqueue(order);
}

void MyOrders::pushOrder(Order::OrderType transactionTyp, qint32 stockId, qint32 amount, qint32 price)
{
    pushOrder(Order(transactionTyp, stockId, amount, price));
}

void MyOrders::removeLastUnassigned()
{
    m_notAssignedOrders.dequeue();
}

bool MyOrders::assigned(qint32 orderId)
{
    if(m_notAssignedOrders.empty())
        return false;

    (*this)[orderId] = m_notAssignedOrders.dequeue();
    return true;
}



void MyOrders::changeOrder(qint32 orderId, qint32 amount)
{
    (*this)[orderId].setAmount(amount);
    if((*this)[orderId].getAmount() == 0)
        remove(orderId);
}



void MyOrders::expire()
{
    m_upToDate = false;
}

bool MyOrders::isUpToDate()
{
    return m_upToDate;
}

#include "stock.h"

Stock::Stock()
{
}

void Stock::setBestSellOrder(QPair<qint32, qint32> order)
{
    m_bestSellOrder = order;
}

void Stock::setBestBuyOrder(QPair<qint32, qint32> order)
{
    m_bestBuyOrder = order;
}

void Stock::newPrice(QPair<QDateTime, QPair<qint32, qint32> > transaction, qint64 historyTime)
{
    if(!transaction.first.isValid())
        return;

    m_priceHistory[transaction.first] = transaction.second;
    while(m_priceHistory.begin().key().secsTo(transaction.first) > historyTime)
        m_priceHistory.erase(m_priceHistory.begin());
}

void Stock::newPrice(qint32 amount, qint32 price, QDateTime time, qint64 historyTime)
{
    if(time.isValid())
        return;
    m_priceHistory[time] = qMakePair(price, amount);
    while(m_priceHistory.begin().key().secsTo(time) > historyTime)
        m_priceHistory.erase(m_priceHistory.begin());
}

qint32 Stock::getBestSellPrice() const
{
    return m_bestSellOrder.first;
}

qint32 Stock::getBestSellAmount() const
{
    return m_bestSellOrder.second;
}

qint32 Stock::getBestBuyPrice() const
{
    return m_bestBuyOrder.first;
}

qint32 Stock::getBestBuyAmount() const
{
    return m_bestBuyOrder.second;
}

double Stock::trendValue(qint64 historyTime) const
{
    if(m_priceHistory.isEmpty())
        return 1;
    QMap<QDateTime, QPair<qint32, qint32> >::const_iterator it = m_priceHistory.end();
    --it;
    return m_priceHistory.lowerBound(it.key().addSecs(-historyTime)).value().first/static_cast<double>(it.value().first);
}

double Stock::greatestPrice(qint64 historyTime) const
{
    if(m_priceHistory.isEmpty())
        return 1;
    QMap<QDateTime, QPair<qint32, qint32> >::const_iterator last = m_priceHistory.end();
    QMap<QDateTime, QPair<qint32, qint32> >::const_iterator it = m_priceHistory.lowerBound((last-1).key().addSecs(-historyTime));

    qint32 ret = (last-1).value().first;
    for(; it != last; ++it)
        if(ret < it.value().first)
            ret = it.value().first;

    return static_cast<double>((last-1).value().first)/ret;
}

double Stock::lowestPrice(qint64 historyTime) const
{
    if(m_priceHistory.isEmpty())
        return 1;
    QMap<QDateTime, QPair<qint32, qint32> >::const_iterator last = m_priceHistory.end();\
    QMap<QDateTime, QPair<qint32, qint32> >::const_iterator it = m_priceHistory.lowerBound((last-1).key().addSecs(-historyTime));

    qint32 ret = (last-1).value().first;
    for(; it != last; ++it)
        if(ret > it.value().first)
            ret = it.value().first;

    return static_cast<double>((last-1).value().first)/ret;
}

double Stock::lowestDiff(qint64 historyTime, qint32 price) const
{
    if(m_priceHistory.isEmpty())
        return 0;
    QMap<QDateTime, QPair<qint32, qint32> >::const_iterator last = m_priceHistory.end();
    QMap<QDateTime, QPair<qint32, qint32> >::const_iterator it = m_priceHistory.lowerBound((last-1).key().addSecs(-historyTime));

    qint32 diff = abs((last-1).value().first - price);
    for(; it != last; ++it)
        if(abs(it.value().first - price) < diff)
            diff = abs(it.value().first - price);

    return diff;
}

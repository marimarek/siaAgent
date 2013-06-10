#ifndef STOCK_H
#define STOCK_H

#include <QDateTime>
#include <QMap>

class Stock
{
    QPair<qint32, qint32> m_bestSellOrder;
    QPair<qint32, qint32> m_bestBuyOrder;
    QMap<QDateTime, QPair<qint32, qint32> > m_priceHistory;

public:
    Stock();

    void setBestSellOrder(QPair<qint32, qint32> order);
    void setBestBuyOrder(QPair<qint32, qint32> order);
    void newPrice(QPair<QDateTime, QPair<qint32, qint32> > transaction, qint64 historyTime = 60);
    void newPrice(qint32 amount, qint32 price, QDateTime time, qint64 historyTime = 60);

    qint32 getBestSellPrice() const;
    qint32 getBestSellAmount() const;
    qint32 getBestBuyPrice() const;
    qint32 getBestBuyAmount() const;

    qint32 lastPrice();

    double trendValue(qint64 historyTime) const;
    double greatestPrice(qint64 historyTime) const;
    double lowestPrice(qint64 historyTime) const;

    double lowestDiff(qint64 historyTime, qint32 price) const;
};

#endif // STOCK_H

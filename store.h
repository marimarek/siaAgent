#ifndef STORE_H
#define STORE_H

#include "order.h"

#include <QMap>
#include <QVector>

class Store
{
    qint32 m_money;
    QMap<qint32, qint32> m_stocks;

    bool m_upToDate;
public:
    Store();

    void setStore(const QVector<QPair<qint32, qint32> > &stocks);

    qint32 getMoney();
    qint32 getStockAmount(qint32 stockId);
    QList<qint32> getStocks();
    bool contains(qint32 stockId);

    bool order(const Order& order);
    void sellTransaction(qint32 stockId, qint32 amount, qint32 price);
    void buyTransaction(qint32 stockId, qint32 amount, qint32 price);

    void expire();
    bool isUpToDate();
};

#endif // STORE_H

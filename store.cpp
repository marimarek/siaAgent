#include "store.h"

Store::Store() : m_money(0), m_upToDate(false)
{   }

void Store::setStore(const QVector<QPair<qint32, qint32> >& stocks)
{
    m_money = 0;
    m_stocks.clear();

    for(int i = 0; i < stocks.size(); ++i)
        if( stocks[i].first == 1)
            m_money = stocks[i].second;
        else if( stocks[i].second != 0)
            m_stocks[stocks[i].first] = stocks[i].second;

    m_upToDate = true;
}

qint32 Store::getMoney()
{
    return m_money;
}

qint32 Store::getStockAmount(qint32 stockId)
{
    return m_stocks.value(stockId);
}

QList<qint32> Store::getStocks()
{
    return m_stocks.keys();
}

bool Store::contains(qint32 stockId)
{
    return m_stocks.contains(stockId);
}

bool Store::order(const Order& order)
{
    if(order.getTransactionType() == Order::SELL)
    {
        if( getStockAmount(order.getStockId()) >= order.getAmount())
        {
            m_stocks[order.getStockId()] -= order.getAmount();
            if(!m_stocks[order.getStockId()])
                m_stocks.remove(order.getStockId());
            return true;
        }
        else return false;
    }
    else if(order.getTransactionType() == Order::BUY)
    {
        if( m_money >= order.getAmount() * order.getPrice())
        {
            m_money -= order.getAmount() * order.getPrice();
            return true;
        }
        else return false;
    }
    else return false;
}

void Store::sellTransaction(qint32 stockId, qint32 amount, qint32 price)
{

}

void Store::buyTransaction(qint32 stockId, qint32 amount, qint32 price)
{

}

void Store::expire()
{
    m_upToDate = false;
}

bool Store::isUpToDate()
{
    return m_upToDate;
}

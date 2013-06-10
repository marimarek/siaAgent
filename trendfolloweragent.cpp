#include "trendfolloweragent.h"

TrendFollowerAgent::TrendFollowerAgent(qint64 upTrendTime, double upTrendValue,
                                       qint64 downTrendTime, double downTrendValue,
                                       double cancelDiffValue,
                                       int msecInIdle, QObject *parent)
    : Agent(msecInIdle, std::max(upTrendTime, downTrendTime), parent),
      m_upTrendTime(upTrendTime), m_upTrendValue(upTrendValue),
      m_downTrendTime(downTrendTime), m_downTrendValue(downTrendValue), m_cancelDiffValue(cancelDiffValue)
{
}


void TrendFollowerAgent::play()
{
    qDebug() << "[Agent] Agent is playing.";
    if(!m_store.isUpToDate() || !m_myOrders.isUpToDate() || m_stocksInfo.size() != STOKS_NUMBER - 1)
    {
        qDebug() << "[Agent] Agent infos aren't up to date.";
        return;
    }
    m_idleTimer->start();

    qint32 money = m_store.getMoney();

    for(int i = 2; i <=  STOKS_NUMBER; ++i)
    {
        if(m_store.contains(i))
        {
            double downTrendValue = m_stocksInfo[i].trendValue(m_downTrendTime);
            if(downTrendValue <= m_downTrendValue)
            {
                qint32 price = m_stocksInfo[i].getBestBuyPrice();

                qint32 maxAmount =  m_store.getStockAmount(i);
                if(maxAmount)
                {
                    qint32 amount = pow(std::min(static_cast<double>(m_downTrendValue)/downTrendValue, 1.15), 10 + static_cast<double>(14*qrand())/RAND_MAX) *
                            (1 + static_cast<double>(2*qrand())/RAND_MAX) * (static_cast<double>(money)/1000000) + 2 + qrand() % 5;
                    amount %= maxAmount;
                    if(amount)
                        sellStock(i, amount, price);
                }
            }
        }
        double upTrendValue = m_stocksInfo[i].trendValue(m_upTrendTime);
        if(upTrendValue >= m_upTrendValue)
        {
            qint32 price = m_stocksInfo[i].getBestSellPrice();
            if(price)
            {
                qint32 maxAmount = money/price;
                if(maxAmount)
                {
                    qint32 amount = pow(std::min(static_cast<double>(upTrendValue)/m_upTrendValue, 1.15), 10 + static_cast<double>(14*qrand())/RAND_MAX) *
                            (1 + static_cast<double>(2*qrand())/RAND_MAX) * (static_cast<double>(money)/1000000) + 2 + qrand() % 5;
                    amount %= maxAmount;
                    if(amount)
                        buyStock(i, amount, price);
                }
            }
        }
    }

    QMapIterator<int, Order> it(m_myOrders);
    while (it.hasNext())
    {
        it.next();
        qint32 bestBuyPrice = m_stocksInfo[it.key()].getBestBuyPrice();
        if(bestBuyPrice/static_cast<double>(it.value().getPrice()) < m_cancelDiffValue)
            cancelReq(it.key());
    }

}

#include "changetrendagent.h"

changeTrendAgent::changeTrendAgent(qint64 greatestBuyTime, qint64 lowestBuyTime, double greatestBuyPrice, double lowestBuyPrice,
                                   qint64 greatestSellTime, qint64 lowestSellTime, double lowestSellPrice, double greatestSellPrice,
                                   double cancelDiffValue,
                                   int msecInIdle, QObject *parent)
    : Agent(msecInIdle, std::max(greatestBuyTime, std::max(lowestBuyTime, std::max(greatestSellTime, lowestSellTime))), parent),
      m_greatestBuyTime(greatestBuyTime), m_lowestBuyTime(lowestBuyTime), m_greatestBuyPrice(greatestBuyPrice), m_lowestBuyPrice(lowestBuyPrice),
    m_greatestSellTime(greatestSellTime), m_lowestSellTime(lowestSellTime), m_lowestSellPrice(lowestSellPrice), m_greatestSellPrice(greatestSellPrice),
      m_cancelDiffValue(cancelDiffValue)
{
}

void changeTrendAgent::play()
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
            double greatestSellPrice = m_stocksInfo[i].greatestPrice(m_greatestSellTime);
            double lowestSellPrice = m_stocksInfo[i].lowestPrice(m_lowestSellTime);
            if(greatestSellPrice >= m_greatestSellPrice && lowestSellPrice <= m_lowestSellPrice)
            {
                qint32 price = m_stocksInfo[i].getBestBuyPrice() + 2 - qrand()%6;

                qint32 maxAmount = m_store.getStockAmount(i);
                if(maxAmount)
                {
                    qint32 amount = pow(std::min(static_cast<double>(m_lowestSellPrice)/lowestSellPrice, 1.15), 10 + static_cast<double>(14*qrand())/RAND_MAX) *
                            (1 + static_cast<double>(2*qrand())/RAND_MAX) * (static_cast<double>(money)/1000000) + 2 + qrand() % 5;
                    amount %= maxAmount;
                    if(amount)
                        sellStock(i, amount, price);
                }
            }
        }
        double greatestBuyPrice = m_stocksInfo[i].greatestPrice(m_greatestBuyTime);
        double lowestBuyPrice = m_stocksInfo[i].lowestPrice(m_lowestBuyTime);
        if(greatestBuyPrice >= m_greatestBuyPrice && lowestBuyPrice <= m_lowestBuyPrice)
        {
            qint32 price = m_stocksInfo[i].getBestSellPrice() - 2 + qrand()%6;
            if(price)
            {
                qint32 maxAmount = money/price;
                if(maxAmount)
                {
                    qint32 amount = pow(std::min(static_cast<double>(greatestBuyPrice)/m_greatestBuyPrice, 1.15), 10 + static_cast<double>(14*qrand())/RAND_MAX) *
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

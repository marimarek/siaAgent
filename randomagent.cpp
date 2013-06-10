#include "randomagent.h"

RandomAgent::RandomAgent(double buyStockChange, double sellStockChange, double cancelChange,
                         int msecInIdle, qint64 historyTime, QObject *parent)
    : Agent(msecInIdle, historyTime, parent),
      m_buyStockChange(buyStockChange), m_sellStockChange(sellStockChange), m_cancelChange(cancelChange)
{
}


void RandomAgent::play()
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
            if(static_cast<double>(qrand())/RAND_MAX < m_sellStockChange)
            {
                qint32 price = m_stocksInfo[i].getBestBuyPrice() + 3 - qrand() % 10;

                qint32 maxAmount = m_store.getStockAmount(i);
                if(maxAmount)
                {
                    qint32 amount = pow(1 + static_cast<double>(0.15*qrand())/RAND_MAX, 10 + static_cast<double>(14*qrand())/RAND_MAX) *
                            (1 + static_cast<double>(2*qrand())/RAND_MAX) * (static_cast<double>(money)/1000000) + 2 + qrand() % 5;
                    amount %= maxAmount;
                    if(amount)
                        sellStock(i, amount, price);
                }
            }
        }
        if(static_cast<double>(qrand())/RAND_MAX < m_buyStockChange)
        {
            qint32 price = m_stocksInfo[i].getBestSellPrice() - 3 + qrand() % 10;
            if(price)
            {
                qint32 maxAmount = money/price;
                if(maxAmount)
                {
                    qint32 amount = pow(1 + static_cast<double>(0.15*qrand())/RAND_MAX, 10 + static_cast<double>(14*qrand())/RAND_MAX) *
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
        if(static_cast<double>(qrand())/RAND_MAX < m_cancelChange)
            cancelReq(it.key());
    }

}

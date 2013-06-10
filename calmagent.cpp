#include "calmagent.h"

calmAgent::calmAgent(qint64 time, double procent, double diff,
                     int msecInIdle, QObject *parent)
    : Agent(msecInIdle, time, parent), m_time(time), m_procent(procent), m_diff(diff)
{
}

void calmAgent::stockInfo(qint32 stockId, QPair<qint32, qint32> bestBuyOrder, QPair<qint32, qint32> bestSellOrder,
                                  QPair<QDateTime, QPair<qint32, qint32> > lastTransaction)
{
    qDebug() << "[Agent] Receive info about stock: " << stockId;
    qDebug() << bestBuyOrder << bestSellOrder;
    m_stocksInfo[stockId].setBestSellOrder(bestSellOrder);
    m_stocksInfo[stockId].setBestBuyOrder(bestBuyOrder);
    m_stocksInfo[stockId].newPrice(lastTransaction, m_historyTime);

    qint32 bestSellPrice = bestSellOrder.first;
    qint32 bestBuyPrice = bestBuyOrder.first;
    qint32 avg = (bestSellPrice + bestBuyPrice)/2;
    if(!bestBuyPrice)
    {
        avg = bestSellPrice;
    }
    if(!bestSellPrice)
    {
        avg = bestBuyPrice;
    }
    if(avg)
        m_myPrognozePrice[stockId] = avg * (0.97 + (0.06 * qrand())/RAND_MAX);

}

void calmAgent::play()
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
            if(m_stocksInfo[i].getBestBuyPrice() >  m_myPrognozePrice[i]*(1 + m_procent*qrand()/RAND_MAX))
            {
                qint32 price = m_stocksInfo[i].getBestBuyPrice();
                if(!price)
                {
                    price =  m_stocksInfo[i].lastPrice() *(0.99 + (0.02 * qrand())/RAND_MAX);
                }
                if(price)
                {
                    qint32 maxAmount = m_store.getStockAmount(i);
                    if(maxAmount)
                    {
                        qint32 amount = m_stocksInfo[i].getBestBuyAmount();
                        amount %= maxAmount;
                        if(amount)
                            sellStock(i, amount, price);
                    }
                }
            }
        }
        if(m_stocksInfo[i].getBestSellPrice() <  m_myPrognozePrice[i]*(1 - m_procent*qrand()/RAND_MAX))
        {
            qint32 price = m_stocksInfo[i].getBestSellPrice();
            if(!price)
            {
                price =  m_stocksInfo[i].lastPrice() *(0.99 + (0.02 * qrand())/RAND_MAX);
            }
            if(price)
            {
                qint32 maxAmount = money/price;
                if(maxAmount)
                {
                    qint32 amount = m_stocksInfo[i].getBestSellAmount();
                    amount %= maxAmount;
                    if(amount)
                        buyStock(i, amount, price);
                }
            }
        }
        if(m_stocksInfo[i].lowestDiff(m_time, m_myPrognozePrice[i]) > m_diff )
        {
            qint32 bestSellPrice = m_stocksInfo[i].getBestSellPrice();
            qint32 bestBuyPrice = m_stocksInfo[i].getBestBuyPrice();
            qint32 avg = (bestSellPrice + bestBuyPrice)/2;
            if(!bestBuyPrice)
            {
                avg = bestSellPrice;
            }
            if(!bestSellPrice)
            {
                avg = bestBuyPrice;
            }
            if(avg)
                m_myPrognozePrice[i] = avg * (0.97 + (0.06 * qrand())/RAND_MAX);
        }
    }

}

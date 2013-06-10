#ifndef CHANGETRENDAGENT_H
#define CHANGETRENDAGENT_H

#include "agent.h"

class changeTrendAgent : public Agent
{
    qint64 m_greatestBuyTime;
    qint64 m_lowestBuyTime;
    double m_greatestBuyPrice;
    double m_lowestBuyPrice;

    qint64 m_greatestSellTime;
    qint64 m_lowestSellTime;
    double m_lowestSellPrice;
    double m_greatestSellPrice;

    double m_cancelDiffValue;
public:
    changeTrendAgent(qint64 greatestBuyTime, qint64 lowestBuyTime, double greatestBuyPrice, double lowestBuyPrice,
                     qint64 greatestSellTime, qint64 lowestSellTime, double lowestSellPrice, double greatestSellPrice,
                     double cancelDiffValue,
                     int msecInIdle, QObject *parent = 0);

    virtual void play();
};

#endif // CHANGETRENDAGENT_H

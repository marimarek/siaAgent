#ifndef RANDOMAGENT_H
#define RANDOMAGENT_H

#include "agent.h"

class RandomAgent : public Agent
{
    double m_buyStockChange;
    double m_sellStockChange;
    double m_cancelChange;
public:
    RandomAgent(double buyStockChange, double sellStockChange, double cancelChange,
            int msecInIdle, qint64 historyTime, QObject *parent = 0);

    virtual void play();
};

#endif // RANDOMAGENT_H

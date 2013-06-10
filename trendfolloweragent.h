#ifndef TRENDFOLLOWERAGENT_H
#define TRENDFOLLOWERAGENT_H

#include "agent.h"

class TrendFollowerAgent : public Agent
{
    Q_OBJECT

    qint64 m_upTrendTime;
    double m_upTrendValue;
    qint64 m_downTrendTime;
    double m_downTrendValue;
    double m_cancelDiffValue;
public:
    TrendFollowerAgent(qint64 upTrendTime, double upTrendValue,
                       qint64 downTrendTime, double downTrendValue,
                       double cancelDiffValue,
                       int msecInIdle, QObject *parent = 0);
public slots:
    virtual void play();
};

#endif // TRENDFOLLOWERAGENT_H

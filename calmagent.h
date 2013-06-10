#ifndef CALMAGENT_H
#define CALMAGENT_H

#include "agent.h"

class calmAgent : public Agent
{
    QMap<qint32, qint32> m_myPrognozePrice;

    qint64 m_time;
    double m_procent;
    double m_diff;
public:
    calmAgent(qint64 time, double procent, double diff,
              int msecInIdle, QObject *parent = 0);

    virtual void stockInfo(qint32 stockId, QPair<qint32, qint32> bestBuyOrder, QPair<qint32, qint32> bestSellOrder,
                                      QPair<QDateTime, QPair<qint32, qint32> > lastTransaction);

    virtual void play();
};

#endif // CALMAGENT_H

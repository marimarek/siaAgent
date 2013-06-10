#ifndef GETSTOCKINFORESPMSG_H
#define GETSTOCKINFORESPMSG_H

#include "imessage.h"

#include <QDateTime>
#include <QPair>

class GetStockInfoRespMsg : public IMessage
{
    qint32 m_stockId;
    QPair<qint32, qint32> m_bestBuyOrder;
    QPair<qint32, qint32> m_bestSellOrder;
    QPair<QDateTime, QPair<qint32, qint32> > m_lastTransaction;
public:
    GetStockInfoRespMsg(QDataStream& in);

    MessageType type() const;
    qint32 getStockId();
    QPair<qint32, qint32> getBestBuyOrder();
    QPair<qint32, qint32> getBestSellOrder();
    QPair<QDateTime, QPair<qint32, qint32> > getLastTransaction();

};

#endif // GETSTOCKINFORESPMSG_H

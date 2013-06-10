#include "getstockinforespmsg.h"

GetStockInfoRespMsg::GetStockInfoRespMsg(QDataStream &in) : IMessage(in)
{
    qint16 dateLength;
    QString date;

    in >> m_stockId
       >> m_bestBuyOrder
       >> m_bestSellOrder
       >> m_lastTransaction.second
       >> dateLength;

    QByteArray buffer(dateLength, Qt::Uninitialized);

    in.readRawData(buffer.data(), dateLength);
    date = QString(buffer);
    m_lastTransaction.first = QDateTime::fromString(date, Qt::ISODate);
}

IOMessage::MessageType GetStockInfoRespMsg::type() const
{
    return GET_STOCK_INFO_RESP;
}

qint32 GetStockInfoRespMsg::getStockId()
{
    return m_stockId;
}

QPair<qint32, qint32> GetStockInfoRespMsg::getBestBuyOrder()
{
    return m_bestBuyOrder;
}

QPair<qint32, qint32> GetStockInfoRespMsg::getBestSellOrder()
{
    return m_bestSellOrder;
}

QPair<QDateTime, QPair<qint32, qint32> > GetStockInfoRespMsg::getLastTransaction()
{
    return m_lastTransaction;
}

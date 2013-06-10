#include "getmystocksrespmsg.h"

GetMyStocksRespMsg::GetMyStocksRespMsg(QDataStream &in) : IMessage(in)
{
    qint32 stocksLength;

    in >> stocksLength;
    m_stocks.resize(stocksLength);

    for(int i = 0; i < stocksLength; ++i)
            in >> m_stocks[i];
}

IOMessage::MessageType GetMyStocksRespMsg::type() const
{
    return GET_MY_STOCKS_RESP;
}

qint32 GetMyStocksRespMsg::numOfStocks()
{
    return m_stocks.size();
}

QPair<qint32, qint32> GetMyStocksRespMsg::operator[](int i)
{
    return m_stocks[i];
}

QVector<QPair<qint32, qint32> > GetMyStocksRespMsg::getStocks()
{
    return m_stocks;
}


#ifndef GETMYSTOCKSRESPMSG_H
#define GETMYSTOCKSRESPMSG_H

#include "imessage.h"

#include <QVector>
#include <QPair>

class GetMyStocksRespMsg : public IMessage
{
    QVector<QPair<qint32, qint32> > m_stocks;

    qint16 length() const;
public:
    GetMyStocksRespMsg(QDataStream& in);

    MessageType type() const;
    qint32 numOfStocks();
    QPair<qint32, qint32> operator[](int i);
    QVector<QPair<qint32, qint32> > getStocks();

};

#endif // GETMYSTOCKSRESPMSG_H

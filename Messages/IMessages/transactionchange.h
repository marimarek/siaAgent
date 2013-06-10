#ifndef TRANSACTIONCHANGE_H
#define TRANSACTIONCHANGE_H

#include "imessage.h"

#include <QDateTime>

class TransactionChange : public IMessage
{
    qint32 m_stockId;
    qint32 m_amount;
    qint32 m_price;
    QDateTime m_date;
public:
    TransactionChange(QDataStream& in);

    MessageType type() const;
    qint32 getStockId();
    qint32 getAmount();
    qint32 getPrice();
    QDateTime getDate();
};


#endif // TRANSACTIONCHANGE_H

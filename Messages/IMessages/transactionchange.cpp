#include "transactionchange.h"

TransactionChange::TransactionChange(QDataStream &in) : IMessage(in)
{
    qint16 dateLength;
    QString date;

    in >> m_stockId
       >> m_amount
       >> m_price
       >> dateLength;

    QByteArray buffer(dateLength, Qt::Uninitialized);

    in.readRawData(buffer.data(), dateLength);
    date = QString(buffer);
    m_date = QDateTime::fromString(date, Qt::ISODate);
}

IOMessage::MessageType TransactionChange::type() const
{
    return TRANSACTION_CHANGE;
}

qint32 TransactionChange::getStockId()
{
    return m_stockId;
}

qint32 TransactionChange::getAmount()
{
    return m_amount;
}

qint32 TransactionChange::getPrice()
{
    return m_price;
}

QDateTime TransactionChange::getDate()
{
    return m_date;
}

#include "szef.h"

Szef::Szef() : Agent(0, 0, 0)
{
    m_userId = 1;
    m_password = "abcdef";
    QObject::disconnect(m_conn, SIGNAL(connected()), this, SLOT(registerMe()) );
    QObject::disconnect(m_conn, SIGNAL(registerOk(qint32)), this, SLOT(login(qint32)) );
    QObject::disconnect(m_conn, SIGNAL(registerFail(QString)), this, SLOT(registerFail(QString)) );
    QObject::disconnect(m_conn, SIGNAL(loginFail(QString)), this, SLOT(loginFail(QString)) );
    QObject::disconnect(m_conn, SIGNAL(unLogon()), this, SLOT(unLogon()) );
    QObject::disconnect(m_conn, SIGNAL(bestOrder(Order)), this, SLOT(bestOrder(Order)) );
    QObject::disconnect(m_conn, SIGNAL(myStocks(QVector<QPair<qint32, qint32> >)), this, SLOT(myStocks(QVector<QPair<qint32, qint32> >)) );
    QObject::disconnect(m_conn, SIGNAL(myOrders(QVector<QPair<qint32, Order> >)), this, SLOT(myOrders(QVector<QPair<qint32, Order> >)) );
    QObject::disconnect(m_conn,
            SIGNAL(stockInfo(qint32, QPair<qint32, qint32>, QPair<qint32, qint32>,
                                QPair<QDateTime, QPair<qint32, qint32> >)), this,
            SLOT(stockInfo(qint32, QPair<qint32, qint32> , QPair<qint32, qint32> ,
                                QPair<QDateTime, QPair<qint32, qint32> > )) );
    QObject::disconnect(m_conn,
            SIGNAL(transactionChange(qint32, qint32, qint32, QDateTime)), this,
            SLOT(transactionChange(qint32, qint32, qint32, QDateTime)) );
    QObject::disconnect(m_conn, SIGNAL(sellTransaction(qint32,qint32)), this, SLOT(sellTransaction(qint32,qint32)) );
    QObject::disconnect(m_conn, SIGNAL(buyTransaction(qint32,qint32)), this, SLOT(buyTransaction(qint32,qint32)) );
    QObject::disconnect(m_conn, SIGNAL(disconnected()), this, SLOT(stop()) );
    QObject::disconnect(m_conn, SIGNAL(orderId(qint32)), this, SLOT(orderId(qint32)) );
    QObject::disconnect(this, SIGNAL(update()), this, SLOT(play()) );
    QObject::disconnect(m_idleTimer, SIGNAL(timeout()), this, SLOT(play()) );
    QObject::connect(m_conn, SIGNAL(connected()), this, SLOT(login()) );
    QObject::connect(this, SIGNAL(end()), this, SLOT(deleteLater()) );
}

void Szef::start()
{
    qDebug() << "[Szef] Szef is starting.";
    for(int i = 2; i <= STOKS_NUMBER; ++i)
    {
        for(int j = 0; j < 20; ++j)
        {
            buyStock(i, 1 + 20.0*qrand()/RAND_MAX, std::min(static_cast<int>(PRICES[i]*(0.98 + 0.015*qrand()/RAND_MAX)), PRICES[i]-1));
            sellStock(i, 1 + 20.0*qrand()/RAND_MAX, std::max(static_cast<int>(PRICES[i]*(1.02 - 0.015*qrand()/RAND_MAX)), PRICES[i]+1));
        }
    }

    emit end();
}

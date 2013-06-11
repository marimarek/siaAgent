#ifndef AGENT_H
#define AGENT_H

#include "connection.h"

#include "buystockreqmsg.h"
#include "cancelordermsg.h"
#include "getmyordermsg.h"
#include "getmystocksmsg.h"
#include "getstockinfomsg.h"
#include "loginuserreqmsg.h"
#include "registeruserreqmsg.h"
#include "sellstockreqmsg.h"
#include "subscribestockmsg.h"
#include "unsubscribestockmsg.h"

#include "myorders.h"
#include "store.h"
#include "stock.h"

#include <QObject>
#include <QString>
#include <QMap>
#include <QDateTime>
#include <QTimer>
#include <QCoreApplication>
#include <QDebug>

class Agent : public QObject
{
    Q_OBJECT
protected:
    static const int STOKS_NUMBER = 21;

    static const int NOT_ASSIGNED = -1;

    static const int PRICES[STOKS_NUMBER + 2];

    Connection* m_conn;

    qint32 m_userId;
    QString m_password;

    MyOrders m_myOrders;

    Store m_store;

    QMap<qint32, Stock> m_stocksInfo;
    qint64 m_historyTime;

    QTimer* m_idleTimer;
public:
    Agent(int msecInIdle, qint64 historyTime, QObject *parent = 0);

    ~Agent();
signals:
    void update();
    
public slots:
    void registerMe();
    void login();
    void login(qint32 userId);
    void getMyStocks();
    void getMyOrders();
    void getStockInfo(qint32 stockId);
    void buyStock(qint32 stockId, qint32 amount, qint32 price);
    void sellStock(qint32 stockId, qint32 amount, qint32 price);
    void subscribeStock(qint32 stockId);
    void cancelReq(qint32 orderId);

    virtual void start();
    virtual void play();
    void stop();

    void registerFail(QString reason);
    void loginFail(QString reason);
    void unLogon();
    void bestOrder(Order order);
    void myStocks(QVector<QPair<qint32, qint32> > stocks);
    void myOrders(QVector<QPair<qint32, Order> > orders);
    virtual void stockInfo(qint32 stockId, QPair<qint32, qint32> bestBuyOrder, QPair<qint32, qint32> bestSellOrder,
                   QPair<QDateTime, QPair<qint32, qint32> > lastTransaction);
    void sellTransaction(qint32 orderId, qint32 amount);
    void buyTransaction(qint32 orderId, qint32 amount);
    void transactionChange(qint32 stockId, qint32 amount, qint32 price, QDateTime time);
    void orderId(qint32 orderId);
    
};

#endif // AGENT_H

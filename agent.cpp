#include "agent.h"

const int Agent::PRICES[STOKS_NUMBER + 2] = {0,0, 4185, 12360, 40, 38000, 1399, 800, 9990, 7600, 7600, 14580, 4084, 16540, 1715, 630, 5449, 3447, 44800, 535, 436, 799};

Agent::Agent(int msecInIdle, qint64 historyTime, QObject *parent) :
    QObject(parent), m_conn(new Connection(this)), m_userId(NOT_ASSIGNED), m_password("abcde"), m_historyTime(historyTime),
    m_idleTimer(new QTimer(this))
{
    qDebug() << "[Agent] Agent is creating.";

    m_idleTimer->setInterval(msecInIdle);

    qsrand(QDateTime::currentDateTime().toMSecsSinceEpoch());

    connect(m_conn, SIGNAL(connected()), SLOT(registerMe()) );

    connect(m_conn, SIGNAL(registerOk(qint32)), SLOT(login(qint32)) );

    connect(m_conn, SIGNAL(registerFail(QString)), SLOT(registerFail(QString)) );

    connect(m_conn, SIGNAL(loginOk()), SLOT(start()) );

    connect(m_conn, SIGNAL(loginFail(QString)), SLOT(loginFail(QString)) );

    connect(m_conn, SIGNAL(unLogon()), SLOT(unLogon()) );

    connect(m_conn, SIGNAL(bestOrder(Order)), SLOT(bestOrder(Order)) );

    connect(m_conn, SIGNAL(myStocks(QVector<QPair<qint32, qint32> >)), SLOT(myStocks(QVector<QPair<qint32, qint32> >)) );

    connect(m_conn, SIGNAL(myOrders(QVector<QPair<qint32, Order> >)), SLOT(myOrders(QVector<QPair<qint32, Order> >)) );

    connect(m_conn,
            SIGNAL(stockInfo(qint32, QPair<qint32, qint32>, QPair<qint32, qint32>,
                                QPair<QDateTime, QPair<qint32, qint32> >)),
            SLOT(stockInfo(qint32, QPair<qint32, qint32> , QPair<qint32, qint32> ,
                                QPair<QDateTime, QPair<qint32, qint32> > )) );

    connect(m_conn,
            SIGNAL(transactionChange(qint32, qint32, qint32, QDateTime)),
            SLOT(transactionChange(qint32, qint32, qint32, QDateTime)) );

    connect(m_conn, SIGNAL(sellTransaction(qint32,qint32)), SLOT(sellTransaction(qint32,qint32)) );

    connect(m_conn, SIGNAL(buyTransaction(qint32,qint32)), SLOT(buyTransaction(qint32,qint32)) );

    connect(m_conn, SIGNAL(disconnected()), SLOT(stop()) );

    connect(m_conn, SIGNAL(orderId(qint32)), SLOT(orderId(qint32)) );

    connect(this, SIGNAL(update()), SLOT(play()) );

    connect(m_idleTimer, SIGNAL(timeout()), SLOT(play()) );

    m_conn->connectToServer();
}

Agent::~Agent()
{
    qDebug() << "[Agent] Agent is deleting,";
}

void Agent::registerMe()
{
    qDebug() << "[Agent] Register user with pass: " << m_password;
    RegisterUserReqMsg msg(m_password);
    m_conn->send(msg);
}

void Agent::login()
{
    qDebug() << "[Agent] Login user, id: " << m_userId << ", pass: " << m_password;
    LoginUserReqMsg msg(m_userId, m_password);
    m_conn->send(msg);
}

void Agent::login(qint32 userId)
{
    qDebug() << "[Agent] Register ok userId assigned: " << userId;
    m_userId = userId;
    login();
}

void Agent::getMyOrders()
{
    qDebug() << "[Agent] My orders request.";

    m_myOrders.expire();
    GetMyOrderMsg msg;
    m_conn->send(msg);
}

void Agent::getMyStocks()
{
    qDebug() << "[Agent] My stocks request.";

    m_store.expire();
    GetMyStocksMsg msg;
    m_conn->send(msg);
}

void Agent::getStockInfo(qint32 stockId)
{
    qDebug() << "[Agent] Request info about stock: " << stockId;
    GetStockInfoMsg msg(stockId);
    m_conn->send(msg);
}

void Agent::subscribeStock(qint32 stockId)
{
    qDebug() << "[Agent] Subscribe stock: " << stockId;
    SubscribeStockMsg msg(stockId);
    m_conn->send(msg);
}

void Agent::cancelReq(qint32 orderId)
{
    qDebug() << "[Agent] Cancel order: " << orderId;
    CancelOrderMsg msg(orderId);
    m_conn->send(msg);

    m_myOrders.remove(orderId);
}

void Agent::buyStock(qint32 stockId, qint32 amount, qint32 price)
{
    qDebug() << "[Agent] Buy " << amount
             << " stocks with id: " << stockId << " with price: " << price;
    BuyStockReqMsg msg(stockId, amount, price);
    m_conn->send(msg);
    m_myOrders.pushOrder(Order::BUY, stockId, amount, price);
    m_store.order(Order(Order::BUY, stockId, amount, price));
}

void Agent::sellStock(qint32 stockId, qint32 amount, qint32 price)
{
    qDebug() << "[Agent] Sell " << amount
             << " stocks with id: " << stockId << " with price: " << price;
    SellStockReqMsg msg(stockId, amount, price);
    m_conn->send(msg);
    m_myOrders.pushOrder(Order::SELL, stockId, amount, price);
    m_store.order(Order(Order::SELL, stockId, amount, price));
}


void Agent::start()
{
    qDebug() << "[Agent] Login ok. Agent is starting.";
    qDebug() << "[Agent] Download information.";
    getMyStocks();
    getMyOrders();
    for(int i = 2; i <= STOKS_NUMBER; ++i)
    {
        getStockInfo(i);
        subscribeStock(i);
    }

    m_idleTimer->start();
}

void Agent::play()
{
    qDebug() << "[Agent] Agent is playing.";
    if(!m_store.isUpToDate() || !m_myOrders.isUpToDate() || m_stocksInfo.size() != STOKS_NUMBER - 1)
    {
        qDebug() << "[Agent] Agent infos aren't up to date.";
        return;
    }
    m_idleTimer->start();


    if(qrand()%2)
    {
        qint32 stockId = qrand()%20 + 2;

        qint32 price = m_stocksInfo.value(stockId).getBestSellPrice();
        if( qrand()%3 <2) //chce kupic
            price += qrand()%10;
        else price -= qrand()%50; //zasadza sie na nizsza cene
        if(price <= 0)
            price = 1;

        qint32 maxAmount = m_store.getMoney()/price;
        if(!maxAmount)
            return;
        qint32 amount = 1 + qrand() % std::min(maxAmount, 20);
        buyStock(stockId, amount, price);
    }
    else
    {
        QList<qint32> stocks = m_store.getStocks();
        if(stocks.size() == 0)
            return;
        qint32 stockId = stocks[qrand() % stocks.size()];
        qint32 price = m_stocksInfo.value(stockId).getBestBuyPrice();
        if( qrand()%3 <2) //chce sprzedac
            price -= qrand()%10;
        else price += qrand()%50; //czeka na lepsza okazje
        if(price <= 0)
            price = 500 + qrand() % 4000;  //jesli nie bylo ceny sami ustalamy cene rynkowa

        qint32 maxAmount = m_store.getStockAmount(stockId);
        if(!maxAmount)
            return;
        qint32 amount = 1 + qrand() % std::min(maxAmount, 20);
        sellStock(stockId, amount, price);
    }
}

void Agent::stop()
{
    qDebug() << "[Agent] Disconnected. Agent is stoping play.";



    qDebug() << "[Agent] Trying to reconnect.";
    m_conn->connectToServer();
}

void Agent::registerFail(QString reason)
{
    qDebug() << "[Agent] Register failed: " << reason;
    QCoreApplication::exit(0x11);
}

void Agent::loginFail(QString reason)
{
    qDebug() << "[Agent] Login failed: " << reason;
    QCoreApplication::exit(0x12);
}

void Agent::unLogon()
{
    qDebug() << "[Agent] Unlogon agent";
    QCoreApplication::exit(0x13);
}

void Agent::bestOrder(Order order)
{
     qDebug() << "[Agent] Receive new best order for: " << order.getStockId();
     if(order.getTransactionType() == Order::SELL)
        m_stocksInfo[order.getStockId()].setBestSellOrder(qMakePair(order.getPrice(), order.getAmount()) );
     else if(order.getTransactionType() == Order::BUY)
        m_stocksInfo[order.getStockId()].setBestBuyOrder(qMakePair(order.getPrice(), order.getAmount()) );
     else
         qDebug() << "[Agent] UNDEFINED type order: " << order.getTransactionType();

     emit update();
}

void Agent::myStocks(QVector<QPair<qint32, qint32> > stocks)
{
    qDebug() << "[Agent] Receive stocks: " << stocks.size();
    m_store.setStore(stocks);

    if(!m_store.isUpToDate() || !m_myOrders.isUpToDate() || m_stocksInfo.size() !=  STOKS_NUMBER - 1)
        emit update();
}

void Agent::myOrders(QVector<QPair<qint32, Order> > orders)
{
    qDebug() << "[Agent] Receive orders: " << orders.size();
    m_myOrders.setOrders(orders);

    if(!m_store.isUpToDate() || !m_myOrders.isUpToDate() || m_stocksInfo.size() !=  STOKS_NUMBER - 1)
        emit update();
}

void Agent::stockInfo(qint32 stockId, QPair<qint32, qint32> bestBuyOrder, QPair<qint32, qint32> bestSellOrder,
                      QPair<QDateTime, QPair<qint32, qint32> > lastTransaction)
{
    qDebug() << "[Agent] Receive info about stock: " << stockId;
    qDebug() << bestBuyOrder << bestSellOrder;
    m_stocksInfo[stockId].setBestSellOrder(bestSellOrder);
    m_stocksInfo[stockId].setBestBuyOrder(bestBuyOrder);
    m_stocksInfo[stockId].newPrice(lastTransaction, m_historyTime);
}

void Agent::sellTransaction(qint32 orderId, qint32 amount)
{
    qDebug() << "[Agent] Sell " << amount << "of order: " << orderId;
    m_myOrders.changeOrder(orderId, amount);

    getMyStocks();
}

void Agent::buyTransaction(qint32 orderId, qint32 amount)
{
    qDebug() << "[Agent] Buy " << amount << "of order: " << orderId;
    m_myOrders.changeOrder(orderId, amount);

    getMyStocks();
}

void Agent::transactionChange(qint32 stockId, qint32 amount, qint32 price, QDateTime time)
{
    qDebug() << "[Agent] New Transaction for: " << stockId;
    m_stocksInfo[stockId].newPrice(amount, price, time, m_historyTime);

    if(!m_store.isUpToDate() || !m_myOrders.isUpToDate() || m_stocksInfo.size() !=  STOKS_NUMBER - 1)
        emit update();
}

void Agent::orderId(qint32 orderId)
{
    if(orderId != -1)
    {
        qDebug() << "[Agent] Last order get id: " << orderId;
        m_myOrders.assigned(orderId);
    }
    else
    {
        qDebug() << "[Agent] Server refused last order.";
        m_myOrders.removeLastUnassigned();

        getMyStocks();
    }
}

#ifndef CONNECTION_H
#define CONNECTION_H

#include "omessage.h"
#include "order.h"

#include <QObject>
#include <QString>
#include <QVector>
#include <QTcpSocket>
#include <QDateTime>
#include <QCoreApplication>
#include <QDebug>

class Connection : public QObject
{
    Q_OBJECT

    QTcpSocket* m_socket;
    QString m_hostName;
    quint16 m_port;

public:
    Connection(QObject *parent = 0, const QString& hostName = "localhost", quint16 port = 12345);

    void connectToServer();

    ~Connection();
public slots:
    void send(OMessage& msg);
private slots:
    void disconect();
    void socketError(QAbstractSocket::SocketError error);
    void processMessages();

signals:
    void connected();
    void disconnected();

    void registerOk(qint32 userId);
    void registerFail(QString reason);
    void loginOk();
    void loginFail(QString reason);
    void unLogon();
    void bestOrder(Order order);
    void myStocks(QVector<QPair<qint32, qint32> > stocks);
    void myOrders(QVector<QPair<qint32, Order> > orders);
    void stockInfo(qint32 stockId, QPair<qint32, qint32> bestBuyOrder, QPair<qint32, qint32> bestSellOrder,
                   QPair<QDateTime, QPair<qint32, qint32> > lastTransaction);
    void sellTransaction(qint32 orderId, qint32 amount);
    void buyTransaction(qint32 orderId, qint32 amount);
    void transactionChange(qint32 stockId, qint32 amount, qint32 price, QDateTime time);
    void orderId(qint32 orderId);
};

#endif // CONNECTION_H

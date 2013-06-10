#include "connection.h"

#include "bestordermsg.h"
#include "getmyordersrespmsg.h"
#include "getmystocksrespmsg.h"
#include "getstockinforespmsg.h"
#include "loginuserrespfail.h"
#include "loginuserrespok.h"
#include "ordermsg.h"
#include "registeruserrespfail.h"
#include "registeruserrespok.h"
#include "selltransactionmsg.h"
#include "buytransactionmsg.h"
#include "transactionchange.h"
#include "orderidresp.h"
#include "unrecognizedusermsg.h"

Connection::Connection(QObject *parent, const QString& hostName, quint16 port) :
    QObject(parent), m_socket(new QTcpSocket(this)), m_hostName(hostName), m_port(port)
{
    qDebug() << "\t[Connection] Connection is creating.";

    connect(m_socket, SIGNAL(disconnected()), SLOT(disconect()) );

    connect(m_socket, SIGNAL(connected()), SIGNAL(connected()) );

    connect(m_socket, SIGNAL(error(QAbstractSocket::SocketError)), SLOT(socketError(QAbstractSocket::SocketError)) );

    connect(m_socket, SIGNAL(readyRead()), SLOT(processMessages()) );

}

void Connection::connectToServer()
{
    qDebug() << "\t[Connection] Trying to connect with server.";
    m_socket->connectToHost(m_hostName, m_port);
}

Connection::~Connection()
{
    qDebug() << "\t[Connection] Connection is deleting.";
}


void Connection::send(OMessage& msg)
{
    qDebug() << "\t[Connection] Msg: " << msg.type() << " is sending.";
    msg.send(m_socket);
}

void Connection::disconect()
{
    qDebug() << "\t[Connection] Conection disconnected.";
    emit disconnected();
}

void Connection::socketError(QAbstractSocket::SocketError error)
{
    qDebug() << "\t[Connection] Socket error: " << error;
    QCoreApplication::exit(0x02);
}


void Connection::processMessages()
{
    while(IMessage::isEnoughData(m_socket))
    {

        IOMessage::MessageType msgType = IMessage::getMsgType(m_socket);

        qDebug() << "\t[Connection] Get msg with id = " << msgType;
        QDataStream data(m_socket);

        switch(msgType)
        {
            case IOMessage::REGISTER_USER_RESP_OK:
            {
                RegisterUserRespOk msg(data);
                emit registerOk(msg.getUserId());
                break;
            }
            case IOMessage::REGISTER_USER_RESP_FAIL:
            {
                RegisterUserRespFail msg(data);
                emit registerFail(msg.getReason());
                break;
            }
            case IOMessage::LOGIN_USER_RESP_OK:
            {
                LoginUserRespOk msg(data);
                emit loginOk();
                break;
            }
            case IOMessage::LOGIN_USER_RESP_FAIL:
            {
                LoginUserRespFail msg(data);
                emit loginFail(msg.getReason());
                break;
            }
            case IOMessage::UNRECOGNIZED_USER:
            {
                UnrecognizedUserMsg msg(data);
                emit unLogon();
                break;
            }
            case IOMessage::ORDER:
            {
                OrderMsg msg(data);
                break;
            }
            case IOMessage::BEST_ORDER:
            {
                BestOrderMsg msg(data);
                emit bestOrder(msg.getOrder());
                break;
            }
            case IOMessage::GET_MY_STOCKS_RESP:
            {
                GetMyStocksRespMsg msg(data);
                emit myStocks(msg.getStocks());
                break;
            }
            case IOMessage::GET_MY_ORDERS_RESP:
            {
                GetMyOrdersRespMsg msg(data);
                emit myOrders(msg.getOrders());
                break;
            }
            case IOMessage::GET_STOCK_INFO_RESP:
            {
                GetStockInfoRespMsg msg(data);
                emit stockInfo(msg.getStockId(), msg.getBestBuyOrder(), msg.getBestSellOrder(), msg.getLastTransaction());
                break;
            }
            case IOMessage::SELL_TRANSACTION:
            {
                SellTransactionMsg msg(data);
                emit sellTransaction(msg.getOrderId(), msg.getAmount());
                break;
            }
            case IOMessage::BUY_TRANSACTION:
            {
                BuyTransactionMsg msg(data);
                emit buyTransaction(msg.getOrderId(), msg.getAmount());
                break;
            }
            case IOMessage::TRANSACTION_CHANGE:
            {
                TransactionChange msg(data);
                emit transactionChange(msg.getStockId(), msg.getAmount(), msg.getPrice(), msg.getDate());
                break;
            }
            case IOMessage::ORDER_ID_RESP:
            {
                OrderIdResp msg(data);
                emit orderId(msg.getOrderId());
                break;
            }
            case IOMessage::UNDEFINED:
            default:
            {
                qDebug() << "\t[Connection] Incorrect msg.";
                QCoreApplication::exit(0x01);
            }
        };
    }
}

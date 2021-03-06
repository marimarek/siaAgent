
#include "iomessage.h"


IOMessage::IOMessage()
{}

IOMessage::MessageType IOMessage::toType(qint8 msgId)
{
    switch(msgId)
    {
        case REGISTER_USER_REQ : return REGISTER_USER_REQ;
        case REGISTER_USER_RESP_OK : return REGISTER_USER_RESP_OK;
        case REGISTER_USER_RESP_FAIL : return REGISTER_USER_RESP_FAIL;
        case LOGIN_USER_REQ : return LOGIN_USER_REQ;
        case LOGIN_USER_RESP_OK : return LOGIN_USER_RESP_OK;
        case LOGIN_USER_RESP_FAIL : return LOGIN_USER_RESP_FAIL;
        case UNRECOGNIZED_USER : return UNRECOGNIZED_USER;
        case SUBSCRIBE_STOCK : return SUBSCRIBE_STOCK;
        case UNSUBSCRIBE_STOCK : return UNSUBSCRIBE_STOCK;
        case SELL_STOCK_REQ : return SELL_STOCK_REQ;
        case BUY_STOCK_REQ : return BUY_STOCK_REQ;
        case SELL_TRANSACTION : return SELL_TRANSACTION;
        case BUY_TRANSACTION : return BUY_TRANSACTION;
        case TRANSACTION_CHANGE : return TRANSACTION_CHANGE;
        case ORDER : return ORDER;
        case BEST_ORDER : return BEST_ORDER;
        case GET_MY_STOCKS : return GET_MY_STOCKS;
        case GET_MY_STOCKS_RESP : return GET_MY_STOCKS_RESP;
        case GET_MY_ORDERS : return GET_MY_ORDERS;
        case GET_MY_ORDERS_RESP : return GET_MY_ORDERS_RESP;
        case GET_STOCK_INFO : return GET_STOCK_INFO;
        case GET_STOCK_INFO_RESP : return GET_STOCK_INFO_RESP;
        case CANCEL_ORDER_REQ : return CANCEL_ORDER_REQ;
        case ORDER_ID_RESP : return ORDER_ID_RESP;

        default : return UNDEFINED;
    };
}

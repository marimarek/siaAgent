QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -Wfloat-equal -Wundef \
                  -Wpointer-arith

QT += \
    network \
    widgets
SOURCES += \
    connection.cpp \
    Messages/iomessage.cpp \
    Messages/OMessages/unsubscribestockmsg.cpp \
    Messages/OMessages/subscribestockmsg.cpp \
    Messages/OMessages/sellstockreqmsg.cpp \
    Messages/OMessages/registeruserreqmsg.cpp \
    Messages/OMessages/loginuserreqmsg.cpp \
    Messages/OMessages/omessage.cpp \
    Messages/OMessages/getstockinfomsg.cpp \
    Messages/OMessages/getmystocksmsg.cpp \
    Messages/OMessages/getmyordermsg.cpp \
    Messages/OMessages/cancelordermsg.cpp \
    Messages/OMessages/buystockreqmsg.cpp \
    Messages/IMessages/unrecognizedusermsg.cpp \
    Messages/IMessages/transactionchange.cpp \
    Messages/IMessages/selltransactionmsg.cpp \
    Messages/IMessages/registeruserrespok.cpp \
    Messages/IMessages/registeruserrespfail.cpp \
    Messages/IMessages/ordermsg.cpp \
    Messages/IMessages/imessage.cpp \
    Messages/IMessages/loginuserrespok.cpp \
    Messages/IMessages/loginuserrespfail.cpp \
    Messages/IMessages/getstockinforespmsg.cpp \
    Messages/IMessages/getmystocksrespmsg.cpp \
    Messages/IMessages/getmyordersrespmsg.cpp \
    order.cpp \
    Messages/IMessages/bestordermsg.cpp \
    Messages/IMessages/buytransactionmsg.cpp \
    agent.cpp \
    main.cpp \
    Messages/IMessages/orderidresp.cpp \
    myorders.cpp \
    store.cpp \
    stock.cpp \
    trendfolloweragent.cpp \
    randomagent.cpp \
    changetrendagent.cpp \
    calmagent.cpp \
    szef.cpp \
    starter.cpp

HEADERS += \
    connection.h \
    Messages/iomessage.h \
    Messages/OMessages/unsubscribestockmsg.h \
    Messages/OMessages/subscribestockmsg.h \
    Messages/OMessages/sellstockreqmsg.h \
    Messages/OMessages/registeruserreqmsg.h \
    Messages/OMessages/loginuserreqmsg.h \
    Messages/OMessages/omessage.h \
    Messages/OMessages/getstockinfomsg.h \
    Messages/OMessages/getmystocksmsg.h \
    Messages/OMessages/getmyordermsg.h \
    Messages/OMessages/cancelordermsg.h \
    Messages/OMessages/buystockreqmsg.h \
    Messages/IMessages/unrecognizedusermsg.h \
    Messages/IMessages/transactionchange.h \
    Messages/IMessages/selltransactionmsg.h \
    Messages/IMessages/registeruserrespok.h \
    Messages/IMessages/registeruserrespfail.h \
    Messages/IMessages/ordermsg.h \
    Messages/IMessages/imessage.h \
    Messages/IMessages/loginuserrespok.h \
    Messages/IMessages/loginuserrespfail.h \
    Messages/IMessages/getstockinforespmsg.h \
    Messages/IMessages/getmystocksrespmsg.h \
    Messages/IMessages/getmyordersrespmsg.h \
    order.h \
    Messages/IMessages/bestordermsg.h \
    Messages/IMessages/buytransactionmsg.h \
    agent.h \
    Messages/IMessages/orderidresp.h \
    myorders.h \
    store.h \
    stock.h \
    trendfolloweragent.h \
    randomagent.h \
    changetrendagent.h \
    calmagent.h \
    szef.h \
    starter.h

INCLUDEPATH += Messages \
    Messages/IMessages \
    Messages/OMessages

DEFINES += QT_NO_DEBUG_OUTPUT

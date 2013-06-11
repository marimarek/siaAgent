#include <QCoreApplication>
#include <QThread>

#include "starter.h"



int main(int argv, char **args)
{
    QCoreApplication app(argv, args);

    Starter starter(NULL);

    return app.exec();
}

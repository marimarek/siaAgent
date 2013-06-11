#include "starter.h"

Starter::Starter(QObject *parent) :
    QObject(parent)
{
    qsrand(QDateTime::currentDateTime().toMSecsSinceEpoch());
    connect(new Szef(), SIGNAL(end()), SLOT(start()));
}


void Starter::start()
{
    for(int i = 0; i < 100; ++i)
    {


        RandomAgent* agent = new RandomAgent(0.04 + (0.1*qrand())/RAND_MAX,
                                             0.06 + (0.15*qrand())/RAND_MAX,
                                             0.01 + (0.05*qrand())/RAND_MAX,
                                             100 + qrand()%500 , 1);
        agent->moveToThread(&threads[i]);
        threads[i].start();
    }

    for(int i = 0; i < 50; ++i)
    {


        TrendFollowerAgent* agent = new TrendFollowerAgent(15 + qrand() % 120, 1.005 + (0.07*qrand())/RAND_MAX,
                                                           15 + qrand() %120, 0.997 - (0.04*qrand())/RAND_MAX,
                                                           0.985 - (0.025*qrand())/RAND_MAX,
                                                           500 + qrand()%1000);
        agent->moveToThread(&threads1[i]);
        threads1[i].start();
    }

    for(int i = 0; i < 50; ++i)
    {


        changeTrendAgent* agent = new changeTrendAgent(15 + qrand() % 120, 3 + qrand() % 5, 1.01 + (0.015*qrand())/RAND_MAX, 0.999 - (0.006*qrand())/RAND_MAX,
                                                       3 + qrand() % 5, 15 + qrand() % 120, 0.995 - (0.01*qrand())/RAND_MAX, 1.001 + (0.004*qrand())/RAND_MAX,
                                                       0.985 - (0.025*qrand())/RAND_MAX,
                                                        500 + qrand()%1000);
        agent->moveToThread(&threads2[i]);
        threads2[i].start();
    }

    for(int i = 0; i < 350; ++i)
    {


        calmAgent* agent = new calmAgent(20 + qrand() % 150, 0.005 + (0.01*qrand())/RAND_MAX, 0.015 + (0.02*qrand())/RAND_MAX,
                                                        500 + qrand()%1000);
        agent->moveToThread(&threads3[i]);
        threads3[i].start();
    }

//    for(int i = 0; i < 50; ++i)
//    {


//        TrendFollowerAgent* agent = new TrendFollowerAgent(15 + qrand() % 120, 0.995 - (0.07*qrand())/RAND_MAX,
//                                                           15 + qrand() %120, 1.005 + (0.07*qrand())/RAND_MAX,
//                                                           0.985 - (0.025*qrand())/RAND_MAX,
//                                                           500 + qrand()%1000);
//        agent->moveToThread(&threads4[i]);
//        threads[i].start();
//    }
}

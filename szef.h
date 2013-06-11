#ifndef SZEF_H
#define SZEF_H

#include "agent.h"

class Szef : public Agent
{
    Q_OBJECT
public:
    Szef();

    virtual void start();
signals:
    void end();
};

#endif // SZEF_H

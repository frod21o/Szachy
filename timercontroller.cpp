#include "timercontroller.h"

TimerController::TimerController(QWidget *parent)
    : QWidget{parent}
{
    seconds.setInterval(1000);
    connect(&seconds, SIGNAL(timeout()), this, SLOT(tick()));

    seconds.start();
}

void TimerController::setup(QLCDNumber *timerTop, QLCDNumber *timerBot)
{
    timers[0] = timerTop;
    timers[1] = timerBot;
    set_timers();
}

void TimerController::set_timers()
{
    QString stringTime;
    stringTime.setNum(time);
    for(int i = 0; i<2;i++)
        timers[i]->display(time);
//        timers[i]->display(stringTime);
    timers[0]->startTimer(1);
}

void TimerController::tick()
{
    timers[0]->display(timers[0]->intValue() - 1);
}

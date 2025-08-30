#ifndef TIMERCONTROLLER_H
#define TIMERCONTROLLER_H

#include <QWidget>
#include <QLCDNumber>
#include <QTimer>

class TimerController: public QWidget
{
    Q_OBJECT

public:
    explicit TimerController(QWidget *parent = nullptr);

    void setup(QLCDNumber *timerTop, QLCDNumber *timerBot);

    QTimer seconds;

    void set_timers();
    void start();
    void stop();
    void next_turn();

    inline void set_time(int time) { this->time = time;};
    inline void set_add_time(int add_time) {this->add_time = add_time;};
private:
    int time = 6;
    int add_time = 1;

    QLCDNumber* timers[2];
private slots:

    void tick();
};

#endif // TIMERCONTROLLER_H

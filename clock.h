#ifndef CLOCK_H
#define CLOCK_H

#include <QObject>
#include <QLCDNumber>
#include <QTimer>
#include "boarddisplay.h"

class Clock : public QObject
{
    Q_OBJECT
public:
    explicit Clock(QObject *parent = nullptr);

    void setup(QLCDNumber *timerTop, QLCDNumber *timerBot, BoardDisplay *boardDisplay);

    void set_timers();

    inline void set_time(int time) { if(!seconds.isActive()) this->time = time;};
    inline void set_add_time(int add_time) { if(!seconds.isActive()) this->add_time = add_time;};
private:
    QTimer seconds;
    QTimer refresher;

    void display_timers();

    int time = 0;
    int add_time = 0;

    QLCDNumber* timers[2];
    QLCDNumber* timerTop;
    QLCDNumber* timerBot;
    int current_time[2];
    bool color_running=1;
    int move_counter = 0;
    bool busy = 0;

    BoardDisplay *boardDisplay;
private slots:

    void seconds_tick();
    void refresher_tick();
signals:
    void begin_the_game();
    void cant_undo(bool i);
    void cant_redo(bool i);
};

#endif // CLOCK_H

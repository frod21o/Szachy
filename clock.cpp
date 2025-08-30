#include "clock.h"

Clock::Clock(QObject *parent)
    : QObject{parent}
{
    seconds.setInterval(1000);
    refresher.setInterval(50);
    connect(&seconds, SIGNAL(timeout()), this, SLOT(seconds_tick()));
    connect(&refresher, SIGNAL(timeout()), this, SLOT(refresher_tick()));
    refresher.start();
}

void Clock::setup(QLCDNumber *timerTop, QLCDNumber *timerBot, BoardDisplay *boardDisplay)
{
    this->timerBot = timerBot;
    this->timerTop = timerTop;
    timers[0] = timerTop;
    timers[1] = timerBot;
    this->boardDisplay = boardDisplay;
    set_timers();
}

void Clock::set_timers()
{
    current_time[0] = time;
    current_time[1] = time;
    display_timers();
}

void Clock::display_timers()
{
    for(int i = 0; i<2;i++)
    {
        QString stringTime;
        if(time && !(BoardData::bot_enabled && BoardData::bot_color == i))
        {
            stringTime.setNum(current_time[i]/60 * 100 + current_time[i]%60);
            while(stringTime.size()<3) stringTime = "0" + stringTime;
            stringTime.insert(stringTime.size()-2, ':');
        }
        else
            stringTime="OFF";
        timers[i]->display(stringTime);
    }
}

void Clock::seconds_tick()
{
    while(busy){}
    if(current_time[color_running])
        current_time[color_running]--;
    display_timers();
    if(current_time[color_running] < 1 && time)
    {
        boardDisplay->boardData->timesUp(color_running);
        boardDisplay->repaint();
        seconds.stop();
    }
}

void Clock::refresher_tick()
{
    busy = 1;
    int state = boardDisplay->boardData->get_game_state();
    if(!seconds.isActive() && state == 0)
    {
        emit begin_the_game();
        seconds.start();
    }

    if(move_counter<boardDisplay->boardData->get_move_num())
    {
        current_time[color_running] += add_time;
        color_running = boardDisplay->boardData->get_turn();
        seconds.stop();
        seconds.start();
        move_counter = boardDisplay->boardData->get_move_num();
    }
    if(state == -1)
    {
        move_counter = 0;
        seconds.stop();
        set_timers();
    }
    if(state == 1 || state == 2 || state == 21) seconds.stop();

    switch(boardDisplay->is_inverting())
    {
    case 0:
        timers[1] = timerTop;
        timers[0] = timerBot;
        break;
    case 1:
        timers[0] = timerTop;
        timers[1] = timerBot;
        break;
    case 2:
        timers[color_running] = timerBot;
        timers[!color_running] = timerTop;
        break;
    }
    display_timers();
    busy = 0;

    if(time)
    {
        emit cant_undo(1);
        emit cant_redo(1);
    }
    else
    {
        if(boardDisplay->boardData->can_undo()) emit cant_undo(0);
        else emit cant_undo(1);
        if(boardDisplay->boardData->can_redo()) emit cant_redo(0);
        else emit cant_redo(1);
    }
}

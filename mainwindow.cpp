#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    clock.setup(ui->timerTop, ui->timerBot, ui->widget);

    connect(&clock, SIGNAL(begin_the_game()), this, SLOT(game_began()));
    connect(&clock, SIGNAL(cant_undo(bool)), this, SLOT(set_undo_disabled(bool)));
    connect(&clock, SIGNAL(cant_redo(bool)), this, SLOT(set_redo_disabled(bool)));

    rules0popup.setWindowTitle("Zasady szachów");
    rules0popup.setText("Standardowe zasady szachowe");
    connect(&rules1popup, SIGNAL(apply()), this, SLOT(apply_checkersRules()) );
    connect(&rules1popup, SIGNAL(finished(int)), this, SLOT(activate()) );
    connect(&rules2popup, SIGNAL(apply()), this, SLOT(apply_specialRules()) );
    connect(&rules2popup, SIGNAL(finished(int)), this, SLOT(activate()) );

    on_actionAutoBlack_triggered();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNoTimer_triggered()
{
    clock.set_time(0);
}


void MainWindow::on_action5_1_triggered()
{
    clock.set_time(5*60);
    clock.set_add_time(1);
}
void MainWindow::on_action10_0_triggered()
{
    clock.set_time(10*60);
    clock.set_add_time(0);
}
void MainWindow::on_action10_5_triggered()
{
    clock.set_time(10*60);
    clock.set_add_time(5);
}
void MainWindow::on_action15_0_triggered()
{
    clock.set_time(15*60);
    clock.set_add_time(0);
}
void MainWindow::on_action15_5_triggered()
{
    clock.set_time(15*60);
    clock.set_add_time(5);
}
void MainWindow::on_action30_0_triggered()
{
    clock.set_time(30*60);
    clock.set_add_time(0);
}

void MainWindow::on_actionChess_triggered()
{
    if(gamemode != 0)
    {
        delete ui->widget->boardData;
        ui->widget->boardData = new ChessBoard;
        ui->widget->new_board_set();
        gamemode = 0;
        clock.set_timers();
        ui->menuClock->setEnabled(1);
        ui->actionRules->setEnabled(1);
        ui->menuAutoMoves->setEnabled(1);
    }
    ui->actionChess->setChecked(1);
    ui->actionCheckers->setChecked(0);
    ui->actionSpecjalMode->setChecked(0);
}

void MainWindow::on_actionCheckers_triggered()
{
    if(gamemode != 1)
    {
        delete ui->widget->boardData;
        ui->widget->boardData = new CheckersBoard;
        ui->widget->new_board_set();
        gamemode = 1;
        clock.set_timers();
        ui->menuClock->setEnabled(1);
        ui->actionRules->setEnabled(1);
        ui->menuAutoMoves->setEnabled(1);
    }
    ui->actionChess->setChecked(0);
    ui->actionCheckers->setChecked(1);
    ui->actionSpecjalMode->setChecked(0);
}

void MainWindow::on_actionSpecjalMode_triggered()
{
    if(gamemode != 2)
    {
        delete ui->widget->boardData;
        ui->widget->boardData = new SGamemodBoard;
        ui->widget->new_board_set();
        gamemode = 2;
        clock.set_timers();
        ui->menuClock->setEnabled(1);
        ui->actionRules->setEnabled(1);
        ui->menuAutoMoves->setEnabled(1);
    }
    ui->actionChess->setChecked(0);
    ui->actionCheckers->setChecked(0);
    ui->actionSpecjalMode->setChecked(1);
}


void MainWindow::game_began()
{
    ui->menuClock->setEnabled(0);
    ui->actionRules->setEnabled(0);
    ui->menuAutoMoves->setEnabled(0);
}

void MainWindow::apply_checkersRules()
{
    CheckersPiece::back_take = rules1popup.get_back_take();
    CheckersPiece::take_obligation = rules1popup.get_take_obligation();
    CheckersQueen::long_queen_move = rules1popup.get_long_queen_move();
}

void MainWindow::apply_specialRules()
{
    if(SGamemodBoard::checkers_color != rules2popup.get_checkers_color())
    {
        SGamemodBoard::checkers_color = rules2popup.get_checkers_color();
        ui->widget->reset();
    }
}

void MainWindow::on_actionClose_triggered()
{
    close();
}

void MainWindow::on_actionAutoActive_triggered()
{
    BoardData::bot_enabled = ui->actionAutoActive->isChecked();
}


void MainWindow::on_actionAutoBlack_triggered()
{
    BoardData::bot_color = 0;
    ui->actionAutoBlack->setChecked(1);
    ui->actionAutoWhite->setChecked(0);
}


void MainWindow::on_actionAutoWhite_triggered()
{
    BoardData::bot_color = 1;
    ui->actionAutoBlack->setChecked(0);
    ui->actionAutoWhite->setChecked(1);
}


void MainWindow::on_actionNewGame_triggered()
{
    ui->widget->reset();
    clock.set_timers();
    ui->menuClock->setEnabled(1);
    ui->actionRules->setEnabled(1);
    ui->menuAutoMoves->setEnabled(1);
}


void MainWindow::on_actionRules_triggered()
{
    switch(gamemode){
    case 0:
        rules0popup.show();
        break;
    case 1:
        this->setDisabled(1);
        rules1popup.show();
        break;
    case 2:
        this->setDisabled(1);
        rules2popup.show();
        break;
    }
}




void MainWindow::on_actionRotationWhite_triggered()
{
    ui->widget->invert(1);
    ui->widget->repaint();
    ui->actionRotationWhite->setChecked(1);
    ui->actionRotationBlack->setChecked(0);
    ui->actionRotationMoving->setChecked(0);

}


void MainWindow::on_actionRotationBlack_triggered()
{
    ui->widget->invert(0);
    ui->widget->repaint();
    ui->actionRotationWhite->setChecked(0);
    ui->actionRotationBlack->setChecked(1);
    ui->actionRotationMoving->setChecked(0);
}


void MainWindow::on_actionRotationMoving_triggered()
{
    ui->widget->invert(2);
    ui->widget->repaint();
    ui->actionRotationWhite->setChecked(0);
    ui->actionRotationBlack->setChecked(0);
    ui->actionRotationMoving->setChecked(1);
}


void MainWindow::on_actionUndo_triggered()
{
    ui->widget->undo();
}


void MainWindow::on_actionRedo_triggered()
{
    ui->widget->redo();
}

void MainWindow::set_undo_disabled(bool i)
{
    ui->actionUndo->setDisabled(i);
}

void MainWindow::set_redo_disabled(bool i)
{
    ui->actionRedo->setDisabled(i);
}


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "clock.h"
#include "checkersrules.h"
#include "specialrules.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_actionNewGame_triggered();

    void on_actionChess_triggered();
    void on_actionCheckers_triggered();
    void on_actionSpecjalMode_triggered();

    void on_actionRules_triggered();

    void on_action5_1_triggered();
    void on_action10_0_triggered();
    void on_action10_5_triggered();
    void on_action15_0_triggered();
    void on_action15_5_triggered();
    void on_action30_0_triggered();
    void on_actionNoTimer_triggered();

    void on_actionRotationWhite_triggered();
    void on_actionRotationBlack_triggered();
    void on_actionRotationMoving_triggered();


    void on_actionAutoActive_triggered();
    void on_actionAutoBlack_triggered();
    void on_actionAutoWhite_triggered();


    void on_actionClose_triggered();

    void game_began();
    void apply_checkersRules();
    void apply_specialRules();
    inline void activate() {this->setDisabled(0);}

    void on_actionUndo_triggered();
    void on_actionRedo_triggered();

    void set_undo_disabled(bool i);
    void set_redo_disabled(bool i);

private:
    Clock clock;

    int gamemode = 0; // 0 - chess, 1 - checkers, 2 chess vs checkers

    QMessageBox rules0popup; //chess
    CheckersRules rules1popup; //checkers
    SpecialRules rules2popup; //special mode

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

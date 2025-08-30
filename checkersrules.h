#ifndef CHECKERSRULES_H
#define CHECKERSRULES_H

#include <QDialog>

namespace Ui {
class CheckersRules;
}

class CheckersRules : public QDialog
{
    Q_OBJECT

public:
    explicit CheckersRules(QWidget *parent = nullptr);
    ~CheckersRules();

    inline bool get_back_take() {return back_take;};
    inline bool get_take_obligation() {return take_obligation;};
    inline bool get_long_queen_move() {return long_queen_move;};

private slots:
    void on_CheckersRules_accepted();

    void on_CheckersRules_rejected();
private:
    Ui::CheckersRules *ui;

    bool back_take = 0;
    bool take_obligation = 0;
    bool long_queen_move = 0;

signals:
    void apply();
};

#endif // CHECKERSRULES_H

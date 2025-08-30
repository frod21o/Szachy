#ifndef SPECIALRULES_H
#define SPECIALRULES_H

#include <QDialog>

namespace Ui {
class SpecialRules;
}

class SpecialRules : public QDialog
{
    Q_OBJECT

public:
    explicit SpecialRules(QWidget *parent = nullptr);
    ~SpecialRules();

    inline bool get_checkers_color() {return checkers_color;}
private slots:
    void on_SpecialRules_accepted();

    void on_SpecialRules_rejected();

private:
    Ui::SpecialRules *ui;

    bool checkers_color=1;

signals:
    void apply();
};

#endif // SPECIALRULES_H

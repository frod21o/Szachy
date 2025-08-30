#include "checkersrules.h"
#include "ui_checkersrules.h"

CheckersRules::CheckersRules(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CheckersRules)
{
    ui->setupUi(this);
}

CheckersRules::~CheckersRules()
{
    delete ui;
}

void CheckersRules::on_CheckersRules_accepted()
{
    back_take = ui->checkBox->isChecked();
    take_obligation = ui->checkBox_2->isChecked();
    long_queen_move = ui->checkBox_3->isChecked();

    emit apply();
}


void CheckersRules::on_CheckersRules_rejected()
{
    ui->checkBox->setChecked(back_take);
    ui->checkBox_2->setChecked(take_obligation);
    ui->checkBox_3->setChecked(long_queen_move);
}



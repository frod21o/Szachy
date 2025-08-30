#include "specialrules.h"
#include "ui_specialrules.h"

SpecialRules::SpecialRules(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SpecialRules)
{
    ui->setupUi(this);

    ui->comboBox->setCurrentIndex(!checkers_color);
}

SpecialRules::~SpecialRules()
{
    delete ui;
}

void SpecialRules::on_SpecialRules_accepted()
{
    checkers_color = !ui->comboBox->currentIndex();

    emit apply();
}


void SpecialRules::on_SpecialRules_rejected()
{
    ui->comboBox->setCurrentIndex(!checkers_color);
}


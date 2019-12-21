#include "confirm.h"
#include "ui_confirm.h"

Confirm::Confirm(QWidget *parent) :
    QDialog(parent,Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint|Qt::Tool),
    ui(new Ui::Confirm)
{
    ui->setupUi(this);
}

Confirm::~Confirm()
{
    delete ui;
}

void Confirm::on_buttonBox_accepted()
{
    this->done(0);
}

void Confirm::on_buttonBox_rejected()
{
    this->done(1);
}

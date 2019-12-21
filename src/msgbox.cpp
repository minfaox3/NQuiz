#include "msgbox.h"
#include "ui_msgbox.h"

MsgBox::MsgBox(QWidget *parent) :
    QDialog(parent,Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint|Qt::Tool),
    ui(new Ui::MsgBox)
{
    ui->setupUi(this);
}

MsgBox::~MsgBox()
{
    delete ui;
}

void MsgBox::on_okButton_clicked()
{
    this->done(0);
}

void MsgBox::SetText(QString text){
    ui->textBrowser->setText(text);
}

#include "nonbtnmsg.h"
#include "ui_nonbtnmsg.h"

NonBtnMsg::NonBtnMsg(QWidget *parent) :
    QDialog(parent,Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint|Qt::Tool),
    ui(new Ui::NonBtnMsg)
{
    ui->setupUi(this);
}

NonBtnMsg::~NonBtnMsg()
{
    delete ui;
}

void NonBtnMsg::end()
{
    this->done(0);
}

void NonBtnMsg::SetText(QString text){
    ui->textBrowser->setText(text);
}

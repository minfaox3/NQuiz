#include "help.h"
#include "ui_help.h"

Help::Help(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Help)
{
    ui->setupUi(this);
    QPixmap startimg("://media/image/icon.png");
    ui->Image_Label->setPixmap(startimg.scaled(ui->Image_Label->width(),ui->Image_Label->height(),Qt::KeepAspectRatio));
    ui->pushButton->hide();
    ui->pushButton_2->hide();
}

Help::~Help()
{
    delete ui;
}

void Help::on_pushButton_2_pressed()
{
    //
}

void Help::on_pushButton_pressed()
{
    //
}

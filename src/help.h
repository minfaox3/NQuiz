#ifndef HELP_H
#define HELP_H

#include <QMainWindow>
#include <QPixmap>

namespace Ui {
class Help;
}

class Help : public QMainWindow
{
    Q_OBJECT

public:
    explicit Help(QWidget *parent = nullptr);
    ~Help();

private slots:
    void on_pushButton_2_pressed();

    void on_pushButton_pressed();

private:
    Ui::Help *ui;
};

#endif // HELP_H

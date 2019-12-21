#ifndef CONFIRM_H
#define CONFIRM_H

#include <QDialog>

namespace Ui {
class Confirm;
}

class Confirm : public QDialog
{
    Q_OBJECT

public:
    explicit Confirm(QWidget *parent = nullptr);
    ~Confirm();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::Confirm *ui;
};

#endif // CONFIRM_H

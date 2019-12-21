#ifndef MSGBOX_H
#define MSGBOX_H

#include <QDialog>

namespace Ui {
class MsgBox;
}

class MsgBox : public QDialog
{
    Q_OBJECT

public:
    explicit MsgBox(QWidget *parent = nullptr);
    void SetText(QString text);
    ~MsgBox();

private slots:
    void on_okButton_clicked();

private:
    Ui::MsgBox *ui;
};

#endif // MSGBOX_H

#ifndef NONBTNMSG_H
#define NONBTNMSG_H

#include <QDialog>

namespace Ui {
class NonBtnMsg;
}

class NonBtnMsg : public QDialog
{
    Q_OBJECT

public:
    explicit NonBtnMsg(QWidget *parent = nullptr);
    void SetText(QString text);
    ~NonBtnMsg();
    void end();

private:
    Ui::NonBtnMsg *ui;
};

#endif // NONBTNMSG_H

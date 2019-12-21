#ifndef QUIZWINDOW_H
#define QUIZWINDOW_H

#include <QMainWindow>
#include <vector>
#include <QString>
#include <QStringList>
#include <QFile>
#include <QTextStream>
#include <unistd.h>
#include <iostream>
#include <sys/stat.h>
#include <string>
#include <utility>
#include <QColor>
#include "updatequiz.h"
#include "help.h"

QT_BEGIN_NAMESPACE
namespace Ui { class QuizWindow; }
QT_END_NAMESPACE

class QuizWindow : public QMainWindow
{
    Q_OBJECT

public:
    QuizWindow(QWidget *parent = nullptr);
    void QuizLoad();
    void ReLoad();
    ~QuizWindow();

private slots:
    void on_pushButton_pressed();

    void on_Yes_Button_pressed();

    void on_No_Button_pressed();

    void on_Choice_1_pressed();

    void on_Choice_2_pressed();

    void on_Choice_3_pressed();

    void on_Choice_4_pressed();

    void on_OkButton_pressed();

    void on_ChangeQuiz_pressed();

    void on_NextButton_pressed();

    void on_UpdateAction_triggered();

    void on_ReGetAction_triggered();

    void on_HelpAction_triggered();

private:
    Ui::QuizWindow *ui;
    UpdateQuiz uq;
    Help h;
    void ShowQuestion();
    void ShowAnswer();
    void ShowMaruBatsu();
    void ShowSentaku();
    void HideMaruBatsu();
    void HideSentaku();
    std::vector<QString>alldata;
    std::vector<std::pair<QString,QString>>kind;
    std::pair<QString,std::vector<std::pair<QString,QString>>>forUp;
    std::vector<std::vector<std::pair<bool,std::pair<QString,std::pair<QString,unsigned int>>>>>question;
    QString ver="";
    bool isfinished=false;
    bool isstarted=false;
    bool isqstart=false;
    bool isread=false;
    unsigned int marubatsu=3;
    unsigned int mode=0;
    unsigned int sentakushi=5;
    unsigned int folders_num;
    unsigned int all_question;
    unsigned int now_question;
    unsigned int now_series=0;
    unsigned int ans=0;
    unsigned int correct_num=0;
};
#endif // QUIZWINDOW_H

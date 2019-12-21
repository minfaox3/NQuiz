#include "quizwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QuizWindow w;
    w.QuizLoad();
    w.show();
    Q_INIT_RESOURCE(NQuiz);
    return a.exec();
}

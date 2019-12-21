#ifndef UPDATEQUIZ_H
#define UPDATEQUIZ_H

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QStringList>
#include <QDebug>
#include <QFile>
#include <QEventLoop>
#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <unistd.h>
#include "msgbox.h"
#include "confirm.h"
#include "nonbtnmsg.h"

class UpdateQuiz
{
public:
    UpdateQuiz();
    void Update(std::pair<QString,std::vector<std::pair<QString,QString>>>version);
    QString Download(QString url);

private:
    MsgBox mb;
    Confirm cf;
    NonBtnMsg nbm;
    QString download;
};

#endif // UPDATEQUIZ_H

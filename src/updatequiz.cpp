#include "updatequiz.h"

UpdateQuiz::UpdateQuiz()
{

}

QString UpdateQuiz::Download(QString url){
    QNetworkRequest request;
    request.setUrl(QUrl(url));
    QNetworkAccessManager dlManager;
    dlManager.setNetworkAccessible( QNetworkAccessManager::Accessible );
    QNetworkReply *reply = dlManager.get( request );
    QEventLoop Loop;
    QObject::connect( reply, SIGNAL(finished()), &Loop, SLOT(quit()) );
    Loop.exec();
    QObject::disconnect( reply, SIGNAL(finished()), &Loop, SLOT(quit()) );
    if( reply->error() != QNetworkReply::NoError ){
        mb.SetText("更新に失敗しました.\nインターネットに接続しているか確認してください.\nサイトとの通信の都合上時間を開けると成功する場合もあります.");
        mb.show();
        return "";
    }
    return QString::fromUtf8(reply->readAll());
}

void UpdateQuiz::Update(std::pair<QString,std::vector<std::pair<QString,QString>>>version){
    QNetworkRequest request;
    QString url="https://minfaox3.github.io/NQuizData/";
    request.setUrl(QUrl(url+"ver.data"));
    QNetworkAccessManager dlManager;
    dlManager.setNetworkAccessible( QNetworkAccessManager::Accessible );
    QNetworkReply *reply = dlManager.get( request );
    QEventLoop Loop;
    QObject::connect( reply, SIGNAL(finished()), &Loop, SLOT(quit()) );
    Loop.exec();
    QObject::disconnect( reply, SIGNAL(finished()), &Loop, SLOT(quit()) );
    if( reply->error() != QNetworkReply::NoError ){
        mb.SetText("更新確認に失敗しました.\nインターネットに接続しているか確認してください.\nサイトとの通信の都合上時間を開けると成功する場合もあります.");
        mb.show();
        return;
    }
    download=QString::fromUtf8(reply->readAll());
    QStringList list;
    QString vd="";
    char direc[256];
    getcwd(direc,255);
    std::string dir=direc;
    list = download.split('\n');
    if(version.first!=list[0]){
        if(cf.exec()==0){
            nbm.show();
            nbm.SetText("更新中です.");
            system(("rm "+dir+"/ver.data").c_str());
            QFile vfile(QString::fromStdString(dir+"/ver.data"));
            if (! vfile.open(QIODevice::WriteOnly)) {
                qDebug() << "ERROR OUTPUT";
                return;
            }
            QTextStream outv(&vfile);
            outv << download;
            vfile.close();
            for(unsigned int i=0;i<list[1].toUInt();i++){
                vd=Download(url+"Quiz/"+QString::number(i+1)+"/ver.data");
                if(vd!=""){
                    QStringList cvl=vd.split("\n");
                    if(cvl[0]!=version.second[i].second){
                        std::string dum=dir+"/Quiz/";
                        system(("rm "+dum+std::to_string(i+1)+"/ver.data").c_str());
                        system(("rm "+dum+std::to_string(i+1)+"/quiz.data").c_str());
                        QFile ofile(QString::fromStdString(dum+std::to_string(i+1)+"/ver.data"));
                        if (! ofile.open(QIODevice::WriteOnly)) {
                            qDebug() << "ERROR OUTPUT";
                            return;
                        }
                        QTextStream out(&ofile);
                        out << vd;
                        ofile.close();
                        vd=Download(url+"Quiz/"+QString::number(i+1)+"/quiz.data");
                        QFile oqfile(QString::fromStdString(dum+std::to_string(i+1)+"/quiz.data"));
                        if (! oqfile.open(QIODevice::WriteOnly)) {
                            qDebug() << "ERROR OUTPUT";
                            return;
                        }
                        QTextStream outq(&oqfile);
                        outq << vd;
                        oqfile.close();
                    }
                    else{
                        continue;
                    }
                }
                else {
                    mb.SetText("更新に失敗しました.\nインターネットに接続しているか確認してください.\nサイトとの通信の都合上時間を開けると成功する場合もあります.");
                    mb.show();
                    return;
                }
            }
            nbm.end();
            mb.SetText("更新が完了しました.");
            mb.show();
        }
        else return;
    }
    else{
        mb.SetText("最新の状態です.更新の必要はありません.");
        mb.show();
    }   
}

#include "quizwindow.h"
#include "ui_quizwindow.h"

QuizWindow::QuizWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::QuizWindow)
{
    ui->setupUi(this);
    QPalette pal = ui->NOTLabel_2->palette();
    QPalette pale = ui->CorrectLabel_2->palette();
    pal.setColor(QPalette::Foreground, QColor("#0000FF"));
    pale.setColor(QPalette::Foreground, QColor("#FF0000"));
    ui->NOTLabel_2->setPalette(pal);
    ui->CorrectLabel_2->setPalette(pale);
    ui->NextButton->hide();
    ui->CorrectLabel->hide();
    ui->CorrectLabel_2->hide();
    ui->NOTLabel->hide();
    ui->NOTLabel_2->hide();
}

QuizWindow::~QuizWindow()
{
    delete ui;
}

void QuizWindow::ShowMaruBatsu(){
    ui->Yes_Button->show();
    ui->No_Button->show();
}

void QuizWindow::ShowSentaku(){
    ui->Choice_1->show();
    ui->Choice_2->show();
    ui->Choice_3->show();
    ui->Choice_4->show();
}

void QuizWindow::HideMaruBatsu(){
    ui->Yes_Button->hide();
    ui->No_Button->hide();
}

void QuizWindow::HideSentaku(){
    ui->Choice_1->hide();
    ui->Choice_2->hide();
    ui->Choice_3->hide();
    ui->Choice_4->hide();
}

void QuizWindow::QuizLoad(){
    if(access("ver.data",F_OK|R_OK)!= -1) {
        QFile file("ver.data");
        if(file.open(QIODevice::ReadOnly)){
            QTextStream istream(&file);
            while(!istream.atEnd()){
                alldata.push_back(istream.readLine());
            }
            file.close();
            if(alldata.size()!=3){
                std::cout<<"ERROR reading ./ver.data\n";
                exit(-1);
            }
            ver=alldata[0];
            folders_num=alldata[1].toUInt();
            ui->QuizTitle->setText(alldata[2]);
            setWindowTitle(alldata[2]+" ver-"+ver+" @ なんでもクイズ");
            struct stat statDirectory;
            char dir[255];
            getcwd(dir,255);
            std::string direc=dir,vfs;
            for(unsigned int i=0;i<folders_num;i++){
                alldata.clear();
                direc=dir;
                direc+="/Quiz/"+std::to_string(i+1);
                if(stat(direc.c_str(),&statDirectory)==0){
                    vfs=direc+"/ver.data";
                    QFile kfile(QString::fromStdString(vfs));
                    if(kfile.open(QIODevice::ReadOnly)){
                        QTextStream kistream(&kfile);
                        while(!kistream.atEnd()){
                            alldata.push_back(kistream.readLine());
                        }
                        kfile.close();
                        if(alldata.size()!=2){
                            std::cout<<"ERROR "+direc+"'s format is illegal.\n";
                            std::cout<<"FILE_LINE:"+std::to_string(alldata.size())+"\n";
                            exit(-1);
                        }
                        kind.push_back(std::make_pair(alldata[1],alldata[0]));
                        vfs=direc+"/quiz.data";
                        QFile qfile(QString::fromStdString(vfs));
                        QString qbuf;
                        QString ques,bb;
                        bool flag;
                        int ct=-1;
                        unsigned int ans;
                        std::vector<std::pair<bool,std::pair<QString,std::pair<QString,unsigned int>>>>bv;
                        if(qfile.open(QIODevice::ReadOnly)){
                            QTextStream qistream(&qfile);
                            while(!qistream.atEnd()){
                                qbuf=qistream.readLine();
                                if(qbuf=="C4"){
                                    if(ct!=-1){
                                        bv.push_back(std::make_pair(flag,std::make_pair(ques,std::make_pair(bb,ans))));
                                    }
                                    flag=true;
                                    ques.clear();
                                    bb.clear();
                                    ans=0;
                                    ct=0;
                                }
                                else if(qbuf=="TF"){
                                    if(ct!=-1){
                                        bv.push_back(std::make_pair(flag,std::make_pair(ques,std::make_pair(bb,ans))));
                                    }
                                    flag=false;
                                    ques.clear();
                                    bb.clear();
                                    ans=0;
                                    ct=0;
                                }
                                else if(qbuf=="END"){
                                    bv.push_back(std::make_pair(flag,std::make_pair(ques,std::make_pair(bb,ans))));
                                    break;
                                }
                                else{
                                    if(ct==0){ques=qbuf;ct++;}
                                    else{
                                        if(ct==1){ans=qbuf.toUInt();ct++;}
                                        else if(ct==2){bb=qbuf;ct++;}
                                        else bb+="\\"+qbuf;
                                    }
                                }
                            }
                            qfile.close();
                            question.push_back(bv);
                        }
                        else {
                            std::cout<<"ERROR "+vfs+" is not exsists.\n";
                            exit(-1);
                        }
                    }
                    else{
                        std::cout<<"ERROR "+vfs+" is not exsists.\n";
                        exit(-1);
                    }
                }
                else{
                    std::cout<<"ERROR "+direc+" is not exsists.\n";
                    exit(-1);
                }
            }
            for(unsigned int i=0;i<kind.size();i++){
                ui->QuizCombo->addItem(kind[i].first+" ver"+kind[i].second);
            }
        }
        else{
            std::cout<<"ERROR reading ./ver.data\n";
            exit(-1);
        }
        forUp=std::make_pair(ver,kind);
        isread=true;
    }else{
        qDebug()<<"./ver.dataが存在しないため追加し次第、再読込をしてください";
    }
}

void QuizWindow::ShowQuestion(){
    ans=question[now_series][now_question].second.second.second;
    QString buf;
    QStringList list;
    unsigned int now=30;
    unsigned int length=question[now_series][now_question].second.first.length();
    while (now<length){
        buf+=question[now_series][now_question].second.first.left(30)+"\n";
        now+=30;
    }
    buf+=question[now_series][now_question].second.first.right(length-(now-30))+"\n";
    ui->Question_label->setText("第"+QString::number(now_question+1)+"問");
    if(question[now_series][now_question].first){
        mode=0;
        ShowSentaku();
        HideMaruBatsu();
        ui->QuestionT_label->setText(buf);
        list=question[now_series][now_question].second.second.first.split('\\');
        if(list.size()!=4){
            std::cout<<"ERROR:FORMAT\n";
            exit(-1);
        }
        ui->Choice1_label->setText("①:"+list[0]);
        ui->Choice2_label->setText("②:"+list[1]);
        ui->Choice3_label->setText("③:"+list[2]);
        ui->Choice4_label->setText("④:"+list[3]);
    }
    else{
        mode=1;
        ShowMaruBatsu();
        HideSentaku();
        ui->QuestionT_label->setText(buf+"○か×か.");
        ui->Choice1_label->setText("①:なし");
        ui->Choice2_label->setText("②:なし");
        ui->Choice3_label->setText("③:なし");
        ui->Choice4_label->setText("④:なし");
    }
}

void QuizWindow::ShowAnswer(){
    if(mode==0){
        if(sentakushi==ans){correct_num++;ui->CorrectLabel->show();ui->CorrectLabel_2->show();}
        else{ui->NOTLabel->show();ui->NOTLabel_2->show();}
    }
    else if(mode==1){
        if(marubatsu==ans){correct_num++;ui->CorrectLabel->show();ui->CorrectLabel_2->show();}
        else{ui->NOTLabel->show();ui->NOTLabel_2->show();}
    }
    ui->Correct_label->setText(QString::number(correct_num));
    if(now_question+1<all_question){now_question++;ui->NextButton->show();}
    else isfinished=true;
    isqstart=false;
}

void QuizWindow::on_pushButton_pressed(){
    if(isread){
    isqstart=true;
    now_question=0;
    correct_num=0;
    isstarted=true;
    isfinished=false;
    ui->NextButton->hide();
    ui->CorrectLabel->hide();
    ui->CorrectLabel_2->hide();
    ui->NOTLabel->hide();
    ui->NOTLabel_2->hide();
    ui->Choice1_label->show();
    ui->Choice2_label->show();
    ui->Choice3_label->show();
    ui->Choice4_label->show();
    ui->Correct_label->setText(QString::number(correct_num));
    ui->QuestionT_label->show();
    ui->Quiz_label->setText(kind[now_series].first+" ver"+kind[now_series].second);
    all_question=question[now_series].size();
    ShowQuestion();}
}

void QuizWindow::on_Yes_Button_pressed()
{
    marubatsu=1;
    sentakushi=5;
    ui->NowChoice_label->setText("○");
}

void QuizWindow::on_No_Button_pressed()
{
    marubatsu=0;
    sentakushi=5;
    ui->NowChoice_label->setText("×");
}

void QuizWindow::on_Choice_1_pressed()
{
    sentakushi=1;
    marubatsu=3;
    ui->NowChoice_label->setText("1");
}

void QuizWindow::on_Choice_2_pressed()
{
    sentakushi=2;
    marubatsu=3;
    ui->NowChoice_label->setText("2");
}
void QuizWindow::on_Choice_3_pressed()
{
    sentakushi=3;
    marubatsu=3;
    ui->NowChoice_label->setText("3");
}
void QuizWindow::on_Choice_4_pressed()
{
    sentakushi=4;
    marubatsu=3;
    ui->NowChoice_label->setText("4");
}

void QuizWindow::on_OkButton_pressed()
{
    if(!isfinished&&isstarted&&isqstart){
        ui->Choice1_label->hide();
        ui->Choice2_label->hide();
        ui->Choice3_label->hide();
        ui->Choice4_label->hide();
        ui->QuestionT_label->hide();
        ShowAnswer();
    }
}

void QuizWindow::on_ChangeQuiz_pressed()
{
    now_series=ui->QuizCombo->currentIndex();
}

void QuizWindow::on_NextButton_pressed()
{
    ui->NextButton->hide();
    ui->CorrectLabel->hide();
    ui->CorrectLabel_2->hide();
    ui->NOTLabel->hide();
    ui->NOTLabel_2->hide();
    ui->Choice1_label->show();
    ui->Choice2_label->show();
    ui->Choice3_label->show();
    ui->Choice4_label->show();
    ui->QuestionT_label->show();
    isqstart=true;
    ShowQuestion();
}

void QuizWindow::on_UpdateAction_triggered(){
    uq.Update(forUp);
    ReLoad();
}

void QuizWindow::ReLoad(){
    ui->NextButton->hide();
    ui->CorrectLabel->hide();
    ui->CorrectLabel_2->hide();
    ui->NOTLabel->hide();
    ui->NOTLabel_2->hide();
    ui->Choice1_label->show();
    ui->Choice2_label->show();
    ui->Choice3_label->show();
    ui->Choice4_label->show();
    ui->QuestionT_label->show();
    ui->QuizCombo->clear();
    alldata.clear();
    kind.clear();
    question.clear();
    ver.clear();
    isfinished=false;
    isstarted=false;
    marubatsu=3;
    mode=0;
    sentakushi=5;
    now_question=0;
    now_series=0;
    ans=0;
    correct_num=0;
    if(access("ver.data",F_OK|R_OK)!= -1) {
        QFile file("ver.data");
        if(file.open(QIODevice::ReadOnly)){
            QTextStream istream(&file);
            while(!istream.atEnd()){
                alldata.push_back(istream.readLine());
            }
            file.close();
            if(alldata.size()!=3){
                std::cout<<"ERROR reading ./ver.data\n";
                exit(-1);
            }
            ver=alldata[0];
            folders_num=alldata[1].toUInt();
            ui->QuizTitle->setText(alldata[2]);
            setWindowTitle(alldata[2]+" ver-"+ver+" @ なんでもクイズ");
            struct stat statDirectory;
            char dir[255];
            getcwd(dir,255);
            std::string direc=dir,vfs;
            for(unsigned int i=0;i<folders_num;i++){
                alldata.clear();
                direc=dir;
                direc+="/Quiz/"+std::to_string(i+1);
                if(stat(direc.c_str(),&statDirectory)==0){
                    vfs=direc+"/ver.data";
                    QFile kfile(QString::fromStdString(vfs));
                    if(kfile.open(QIODevice::ReadOnly)){
                        QTextStream kistream(&kfile);
                        while(!kistream.atEnd()){
                            alldata.push_back(kistream.readLine());
                        }
                        kfile.close();
                        if(alldata.size()!=2){
                            std::cout<<"ERROR "+direc+"'s format is illegal.\n";
                            std::cout<<"FILE_LINE:"+std::to_string(alldata.size())+"\n";
                            exit(-1);
                        }
                        kind.push_back(std::make_pair(alldata[1],alldata[0]));
                        vfs=direc+"/quiz.data";
                        QFile qfile(QString::fromStdString(vfs));
                        QString qbuf;
                        QString ques,bb;
                        bool flag;
                        int ct=-1;
                        unsigned int ans;
                        std::vector<std::pair<bool,std::pair<QString,std::pair<QString,unsigned int>>>>bv;
                        if(qfile.open(QIODevice::ReadOnly)){
                            QTextStream qistream(&qfile);
                            while(!qistream.atEnd()){
                                qbuf=qistream.readLine();
                                if(qbuf=="C4"){
                                    if(ct!=-1){
                                        bv.push_back(std::make_pair(flag,std::make_pair(ques,std::make_pair(bb,ans))));
                                    }
                                    flag=true;
                                    ques.clear();
                                    bb.clear();
                                    ans=0;
                                    ct=0;
                                }
                                else if(qbuf=="TF"){
                                    if(ct!=-1){
                                        bv.push_back(std::make_pair(flag,std::make_pair(ques,std::make_pair(bb,ans))));
                                    }
                                    flag=false;
                                    ques.clear();
                                    bb.clear();
                                    ans=0;
                                    ct=0;
                                }
                                else if(qbuf=="END"){
                                    bv.push_back(std::make_pair(flag,std::make_pair(ques,std::make_pair(bb,ans))));
                                    break;
                                }
                                else{
                                    if(ct==0){ques=qbuf;ct++;}
                                    else{
                                        if(ct==1){ans=qbuf.toUInt();ct++;}
                                        else if(ct==2){bb=qbuf;ct++;}
                                        else bb+="\\"+qbuf;
                                    }
                                }
                            }
                            qfile.close();
                            question.push_back(bv);
                        }
                        else {
                            std::cout<<"ERROR "+vfs+" is not exsists.\n";
                            exit(-1);
                        }
                    }
                    else{
                        std::cout<<"ERROR "+vfs+" is not exsists.\n";
                        exit(-1);
                    }
                }
                else{
                    std::cout<<"ERROR "+direc+" is not exsists.\n";
                    exit(-1);
                }
            }
            for(unsigned int i=0;i<kind.size();i++){
                ui->QuizCombo->addItem(kind[i].first+" ver"+kind[i].second);
            }
        }
        else{
            std::cout<<"ERROR reading ./ver.data\n";
            exit(-1);
        }
    }else{
        std::cout<<"ERROR reading ./ver.data\n";
        exit(-1);
    }
    forUp=std::make_pair(ver,kind);
}

void QuizWindow::on_ReGetAction_triggered(){
    ReLoad();
}

void QuizWindow::on_HelpAction_triggered(){
    h.show();
}

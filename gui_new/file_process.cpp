#include "file_process.h"
#include <QDialog>
#include <QAction>
#include <QWidget>
#include <QDebug>
#include <QFileDialog>
#include <QMenuBar>
#include <QMessageBox>
#include <QStatusBar>
#include <QToolBar>
#include <QLineEdit>
#include <QFile>
#include <QSize>
#include <string>
#include <QTextStream>
#include <QDataStream>
#include <vector>
#include <QPushButton>
#include <QLabel>
#include <QPainter>
#include <QKeyEvent>
#include <QKeySequence>
#include <QString>
#include <QCloseEvent>

void FileProcess::create_file(){
    qDebug()<<"create(): create new file!";
    OpenSignal = true;
    CreateSignal = true;
}

void FileProcess::open_file(QString path){
    OpenSignal = true;
    FilePath = path;
    QFile file(path);
    if(!file.open(QFile::ReadOnly|QFile::Text)){
        qDebug()<<"open(): file open error!";
        file.close();
    }else{
        qDebug()<<"open(): file open success!";
        Data.clear();
        while(!file.atEnd()){
            Data.push_back(file.readLine().toStdString());
        }
        //for(int i = 0;i < data.size();++i)
          //  qDebug()<<QString::fromStdString(data[i]);
        file.close();
    }
}

void FileProcess::save_file(QString path){
    if(OpenSignal){
        if(CreateSignal){
            FilePath = path;
        }
        QFile file(FilePath);
        if(file.open(QIODevice::WriteOnly)){
            qDebug() <<"save: File save success!";
            QTextStream out(&file);
            for(int i = 0; i < Data.size(); ++i){
                out<<QString::fromStdString(Data[i]);
            }
            file.close();
        }else{
            qDebug() <<"save: File save error!";
        }
    }
    CreateSignal = false;
    EditedSignal = false;
}

void FileProcess::save_as(QString path){
    FilePath = path;
    QFile file(FilePath);
    if(file.open(QIODevice::WriteOnly)){
        qDebug() <<"save as: File save success!"<<endl;
        QTextStream out(&file);
        for(int i = 0; i < Data.size(); ++i){
            out<<QString::fromStdString(Data[i]);
        }
        file.close();
    }else{
        qDebug() <<"save as: File save error!"<<endl;
    }
    CreateSignal = false;
    EditedSignal = false;
}

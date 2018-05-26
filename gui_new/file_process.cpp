#include "file_process.h"
#include <QDialog>
#include <QWidget>
#include <QDebug>
#include <QFileDialog>
#include <QFile>
#include <string>
#include <QTextStream>
#include <QDataStream>
#include <vector>

void FileProcess::create_file(){
    qDebug()<<"create(): create new file!";
    OpenSignal = true;
    CreateSignal = true;
}

void FileProcess::open_file(QString path){
    OpenSignal = true;
    FilePath = path;
    std::string temp;
    QFile file(path);
    if(!file.open(QFile::ReadOnly|QFile::Text)){
        qDebug()<<"open(): file open error!";
        file.close();
    }else{
        qDebug()<<"open(): file open success!";
        Data.clear();
        while(!file.atEnd()){
            temp = file.readLine().toStdString();
            Data.push_back(temp);
            //Memory->AddStringEnd(temp);
        }
        //for(int i = 0;i < data.size();++i)
          //  qDebug()<<QString::fromStdString(data[i]);
        file.close();
    }
}

void FileProcess::save_file(QString path){
    std::string temp;
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
    std::string temp;
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

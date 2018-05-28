#include "file_process.h"

void FileProcess::create_file(){
    qDebug()<<"create(): create new file!";
    Memory->Clear();
    OpenSignal = true;
    CreateSignal = true;
    EditedSignal = false;
}

void FileProcess::open_file(QString path){
    OpenSignal = true;
    EditedSignal = false;
    FilePath = path;
    std::string temp;
    QFile file(path);
    if(!file.open(QFile::ReadOnly|QFile::Text)){
        qDebug()<<"open(): file open error!";
        file.close();
    }else{
        qDebug()<<"open(): file open success!";
        Memory->Clear();
        Data.clear();
        while(!file.atEnd()){
            temp = file.readLine().toStdString();
            temp.pop_back();
            if(temp == "\u0000") {
                temp = "";
            }
            Data.push_back(temp);
            Memory->AddStringEnd(temp);
        }
        qDebug()<<"open: "<<Memory->GetNumOfLines()<<" lines";
        for(int i = 0; i < Memory->GetNumOfLines(); ++i){
            qDebug()<<QString::fromStdString(Memory->GetIthString(i));
        }
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
            QTextStream out(&file);
            std::string temp;
            Data.clear();
            qDebug()<<"save: "<<Memory->GetNumOfLines()<<" lines";
            for(int i = 0; i < Memory->GetNumOfLines(); ++i){
                temp = Memory->GetIthString(i);
                temp = temp+"\n";
                Data.push_back(temp);
                out<<QString::fromStdString(temp);
            }
            file.close();
            qDebug() <<"save: File save success!";
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
        QTextStream out(&file);
        std::string temp;
        Data.clear();
        qDebug()<<"save_as: "<<Memory->GetNumOfLines()<<" lines";
        for(int i = 0; i < Memory->GetNumOfLines(); ++i){
            temp = Memory->GetIthString(i);
            temp = temp+"\n";
            Data.push_back(temp);
            out<<QString::fromStdString(temp);
        }
        file.close();
        qDebug() <<"save as: File save success!";
    }else{
        qDebug() <<"save as: File save error!"<<endl;
    }
    CreateSignal = false;
    EditedSignal = false;
}

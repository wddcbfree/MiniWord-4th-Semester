#pragma once
#ifndef FILE_PROCESS_H
#define FILE_PROCESS_H
#include <QObject>
#include <QMainWindow>
#include <QFile>
#include <string>
#include <QTextStream>
#include <QDataStream>
#include <vector>
#include <QVector>
#include "memory_new.h"

class FileProcess : public QObject
{
    Q_OBJECT
public:
    void init_memory(Text *memory){
        Memory = memory;
    }
    std::vector<std::string> get_data(){
        return Data;
    }
    void pre_set_data(){
        Data.clear();
    }
    void set_data(std::string line){
        Data.push_back(line);
    }
    void clearData(){
        Data.clear();
    }
    bool is_create(){
        return CreateSignal;
    }
    bool is_open(){
        return OpenSignal;
    }
    bool is_edited(){
        return EditedSignal;
    }
public slots:
    void open_file(QString path);
    void create_file();
    void save_file(QString path);
    void save_as(QString path);
private:
    bool CreateSignal = false;
    bool OpenSignal = false;
    bool EditedSignal = false;
    QString FilePath;
    std::vector<std::string> Data;

    Text *Memory;//数据结构部分
};

#endif // FILE_PROCESS_H

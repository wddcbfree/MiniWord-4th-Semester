#pragma once
#ifndef FILE_PROCESS_H
#define FILE_PROCESS_H
#include <QObject>
#include <QMainWindow>
#include <QFile>
#include <string>
#include <QTextStream>
#include <QDataStream>
#include <QVector>
#include <QDebug>
#include "memory_new.h"

class FileProcess : public QObject {
    Q_OBJECT
public:
    void init_memory(Text *memory) {
        Memory = memory;
    }
    QVector<QString> get_data() {
        return Data;
    }
    void pre_set_data() {
        Data.clear();
    }
    void set_data(QString line) {
        Data.push_back(line);
    }
    void clearData() {
        Data.clear();
    }
    bool is_create() {
        return CreateSignal;
    }
    bool is_open() {
        return OpenSignal;
    }
    bool is_edited() {
        return EditedSignal;
    }
    void set_edited(bool is_not) {
        EditedSignal = is_not;
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
    //std::vector<std::string> Data;
    QVector<QString> Data;
    Text *Memory;//数据结构部分
};

#endif // FILE_PROCESS_H

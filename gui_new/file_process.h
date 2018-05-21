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

class FileProcess : public QObject
{
    Q_OBJECT
public:
    std::vector<std::string> get_data(){
        return Data;
    }
    void set_data(std::vector<std::string> data){
        Data.assign(data.begin(),data.end());
    }
    bool is_create(){
        return CreateSignal;
    }
    bool is_open(){
        return OpenSignal;
    }
public slots:
    void open_file(QString path);
    void create_file();
    void save_file(QString path);
    void save_as(QString path);
signals:
    void ReturnFileName(QString name);
private:
    QMainWindow *parent;
    bool CreateSignal = false;
    bool OpenSignal = false;
    QString FilePath;
    std::vector<std::string> Data;
};

#endif // FILE_PROCESS_H

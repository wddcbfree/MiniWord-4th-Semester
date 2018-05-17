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
    void new_file();
public slots:
    void open_file(QString path);
private:
    std::vector<std::string> data;
};

#endif // FILE_PROCESS_H

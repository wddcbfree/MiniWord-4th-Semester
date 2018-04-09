#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <string>
#include <QTextStream>
#include <QDataStream>
#include <vector>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    std::vector<QString> data;

    bool open();
    void create();
    void prewrite();
    void write(QString line);
    void save();
    void saveas();

private:
    QString path;
    QAction *openAction;
    QAction *saveAction;
    QAction *saveasAction;
    QAction *createAction;
};

#endif // MAINWINDOW_H

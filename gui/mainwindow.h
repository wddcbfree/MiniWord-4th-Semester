#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <string>
#include <QTextStream>
#include <QDataStream>
#include <vector>
#include "dialog.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    bool open();
    QString read(int row);
    void create();
    void prewrite();
    void write(QString line);
    void save();
    void saveas();

protected:
    QKeyEvent *Key;
    void keyReleaseEvent(QKeyEvent *);
private:
    QString path;
    std::vector<QString> data;

    QLineEdit Input;

    QAction *openAction;
    QAction *saveAction;
    QAction *saveasAction;
    QAction *createAction;
};

#endif // MAINWINDOW_H

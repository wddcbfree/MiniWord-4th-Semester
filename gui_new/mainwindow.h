#pragma once
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
#include <vector>
#include <QCloseEvent>
#include <QVector>
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
#include <QSize>
#include <vector>
#include <QPushButton>
#include <QLabel>
#include <QPainter>
#include <QKeyEvent>
#include <QKeySequence>
#include <QString>
#include <QCloseEvent>
#include <QTimer>
#include <QDebug>
#include "file_process.h"
#include "memory_new.h"
#include "screen.h"

class Screen;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void init_file(FileProcess *file_part){
       filepart = file_part;
    }
    void init_memory(Text *memory){
        Memory = memory;
    }
signals:
    void SendCreateSignal();
    void SendOpenPath(QString path);
    void SendSavePath(QString path);
    void SendSaveAsPath(QString path);
protected:
    void keyReleaseEvent(QKeyEvent *);
    //void paintEvent(QPaintEvent *);
    void closeEvent(QCloseEvent *event);
private:
    void create();
    void open();
    void save();
    void save_as();

    void search();

    void input_return_pressed();

    QAction *createAction;
    QAction *openAction;
    QAction *saveAction;
    QAction *saveasAction;
    QAction *quitAction;

    QAction *searchAction;
    QAction *replaceAction;
    QAction *selectAction;

    QLineEdit Input;
    QLabel InputTips;

    FileProcess *filepart;
    Text *Memory;

    Screen screen;
private slots:
    void DisplayScreen();
};

#endif // MAINWINDOW_H

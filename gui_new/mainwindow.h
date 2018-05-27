#pragma once
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QCloseEvent>
#include <QDialog>
#include <QAction>
#include <QWidget>
#include <QFileDialog>
#include <QMenuBar>
#include <QMessageBox>
#include <QStatusBar>
#include <QToolBar>
#include <QLineEdit>
#include <QSize>
#include <QPushButton>
#include <QPainter>
#include <QKeyEvent>
#include <QKeySequence>
#include <QScrollArea>
#include <QCloseEvent>
#include <QTimer>
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
    void select();

    QAction *createAction;
    QAction *openAction;
    QAction *saveAction;
    QAction *saveasAction;
    QAction *quitAction;
    QAction *searchAction;
    QAction *replaceAction;
    QAction *selectAction;

    int row1,col1,row2,col2;
    bool SelectTriggered = false;
    bool Select1 = false;
    bool Select2 = false;
    bool Selected = false;

    QLineEdit Input;
    QLabel InputTips;

    FileProcess *filepart;
    Text *Memory;

    Screen screen;
private slots:
    void DisplayScreen();
};

#endif // MAINWINDOW_H

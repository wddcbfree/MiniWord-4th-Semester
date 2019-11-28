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

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void init_file(FileProcess *file_part) {
        filepart = file_part;
    }
    void init_memory(Text *memory) {
        Memory = memory;
    }
signals:
    void SendCreateSignal();
    void SendOpenPath(QString path);
    void SendSavePath(QString path);
    void SendSaveAsPath(QString path);
protected:
    void keyPressEvent(QKeyEvent *);
    void keyReleaseEvent(QKeyEvent *);
    //void paintEvent(QPaintEvent *);
    void closeEvent(QCloseEvent *event);
private:
    void create();
    void open();
    void save();
    void save_as();
    void search();

    void block_copy() {
        col1 = col_; row1 = row_;
        col2 = Memory->GetCursorCol(); row2 = Memory->GetCursorRow();
        qDebug() << "Block Copied! " << row1 << "," << col1 << "  " << row2 << "," << col2;
        Memory->BlockCopy(row1, col1, row2, col2);
        statusBar()->showMessage("块复制成功！");
        screen.CursorMode();
        //取消高亮
        screen.LoadScreen(*Memory);
    }
    void block_paste() {
        Memory->BlockPaste();
        screen.LoadScreen(*Memory);
        qDebug() << "Block Pasted!";
    }

    QAction *createAction;
    QAction *openAction;
    QAction *saveAction;
    QAction *saveasAction;
    QAction *quitAction;
    QAction *searchAction;
    QAction *replaceAction;
    QAction *copyAction;
    QAction *pasteAction;

    int row_ = -1, col_ = -1, row1 = -1, col1 = -1, row2 = -1, col2 = -1;

    bool SelectTriggered = false;
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

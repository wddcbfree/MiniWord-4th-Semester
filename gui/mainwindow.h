#pragma once
#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <QMainWindow>
#include <QFile>
#include <string>
#include <QTextStream>
#include <QDataStream>
#include <vector>
#include <QVector>
#include "dialog.h"
#include "screen_cache.h"
#include "stl_implement_text_class.h"

#define LINE_WIDTH 700
#define LINE_HIGHT 10
#define TEXT_UPPER_BLANK 100
#define TEXT_LEFT_BLANK 50

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    bool open();
    //QString read(int row);
    void create();
    void prewrite();
    void write(QString line);
    void save();
    void pre_saveas();
    void saveas();

    void RefreshScreen(ScreenCache screen_cache);

protected:
    void keyReleaseEvent(QKeyEvent *);
    void paintEvent(QPaintEvent *);
private:
    void getInputText();
    void InitiateSceen();
    ScreenCache b;
    Text a;

    QString InputText;
    QString path;
    std::vector<QString> data;

    QLineEdit Input;
    QLabel InputTips;

    QAction *openAction;
    QAction *saveAction;
    QAction *saveasAction;
    QAction *createAction;

    QVector<QLabel *> screen_data_;
};

#endif // MAINWINDOW_H_

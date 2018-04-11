#pragma once
#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <QMainWindow>
#include <QFile>
#include <string>
#include <QTextStream>
#include <QDataStream>
#include <vector>
#include <QCloseEvent>
#include <QVector>
#include "dialog.h"
#include "stl_implement_text_class.h"

#define LINE_WIDTH 700
#define LINE_HIGHT 12
#define TEXT_UPPER_BLANK 25
#define TEXT_LEFT_BLANK 50

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    bool open();
    //QString read(int row);
    void precreate();
    void create();
    void prewrite();
    void write(QString line);
    void save();
    void pre_saveas();
    void saveas();

    void RefreshScreen(Text text);

protected:
    void keyReleaseEvent(QKeyEvent *);
    void paintEvent(QPaintEvent *);
    void closeEvent(QCloseEvent *event);
private:
    void getInputText();
    void InitiateSceen();
    Text a;

    QString InputText;
    QString path;
    std::vector<QString> data;

    QLineEdit Input;
    QLabel InputTips;

    QAction *createAction;
    QAction *openAction;
    QAction *saveAction;
    QAction *saveasAction;


    QVector<QLabel *> screen_data_;
};

#endif // MAINWINDOW_H_

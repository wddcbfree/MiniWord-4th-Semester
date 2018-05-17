#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMainWindow>
#include <QFile>
#include <string>
#include <QTextStream>
#include <QDataStream>
#include <vector>
#include <QCloseEvent>
#include <QVector>

#define LINE_WIDTH 700
#define LINE_HIGHT 12
#define TEXT_UPPER_BLANK 40
#define TEXT_LEFT_BLANK 50

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void open();
signals:
    void SendPath(QString path);
private:
    QAction *createAction;
    QAction *openAction;
    QAction *saveAction;
    QAction *saveasAction;

};

#endif // MAINWINDOW_H

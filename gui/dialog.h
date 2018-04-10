#ifndef DIALOG_H
#define DIALOG_H

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
#include <QFile>
#include <QSize>
#include <string>
#include <QTextStream>
#include <QDataStream>
#include <vector>
#include <QPushButton>
#include <QLabel>
#include "mainwindow.h"

class Dialog
{
public:
    QString text();
    void setTips(QString tips);
    Dialog(QWidget *parent = 0);
private slots:

private:
    QPushButton OK;
    QLabel Tips;
};

#endif // DIALOG_H

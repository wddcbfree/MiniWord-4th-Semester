#ifndef INPUTWINDOW_H
#define INPUTWINDOW_H

#include <QAction>
#include <QWidget>
#include <QDebug>
#include <QFileDialog>
#include <QMenuBar>
#include <QMessageBox>
#include <QStatusBar>
#include <QToolBar>
#include <QDialog>
#include <QLineEdit>
#include <QFile>
#include <string>
#include <QTextStream>
#include <QDataStream>
#include <vector>
#include "mainwindow.h"

class input_dialog: public QDialog
{
public:
    input_dialog(QWidget *parent = 0);
    QString text();
private:
    QLineEdit Input;
};

#endif // INPUTWINDOW_H

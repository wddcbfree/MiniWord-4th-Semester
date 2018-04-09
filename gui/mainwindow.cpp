#include <QAction>
#include <QDebug>
#include <QFileDialog>
#include <QMenuBar>
#include <QMessageBox>
#include <QStatusBar>
#include <QToolBar>
#include <QDialog>

#include "mainwindow.h"
using namespace std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setWindowTitle(tr("MiniWord"));

    openAction = new QAction(tr("打开..."), this);
    openAction->setShortcuts(QKeySequence::Open);
    openAction->setStatusTip(tr("Open an existing file"));
    connect(openAction, &QAction::triggered, this, &MainWindow::open);

    saveAction = new QAction(tr("保存"), this);
    saveAction->setShortcuts(QKeySequence::Save);
    saveAction->setStatusTip(tr("Save current file"));
    connect(saveAction, &QAction::triggered, this, &MainWindow::save);

    saveasAction = new QAction(tr("另存为..."), this);
    saveasAction->setShortcuts(QKeySequence::SaveAs);
    saveasAction->setStatusTip(tr("Save as..."));
    connect(saveasAction, &QAction::triggered, this, &MainWindow::saveas);

    QMenu *file = menuBar()->addMenu(tr("&文件"));
    file->addAction(openAction);
    file->addAction(saveAction);
    file->addAction(saveasAction);
    QMenu *info = menuBar()->addMenu(tr("&关于"));
    info->addSection("hello");


   /* QToolBar *toolBar = addToolBar(tr("&File"));
    toolBar->setToolTip("hello");
    toolBar->addAction(openAction);
    */
    statusBar() ;
}

MainWindow::~MainWindow()
{
}

bool MainWindow::open()//打开文件，若打开成功，将所有数据读取到容器 data 中（QString）
{
    path = QFileDialog::getOpenFileName(this,tr("打开..."));
    QFile file(path);
    if(!file.open(QFile::ReadOnly|QFile::Text)){
        qDebug()<<"open(): file open error!"<<endl;
        file.close();
        return false;
    }else{
        qDebug()<<"open(): file open success!"<<endl;
        data.clear();
        while(!file.atEnd()){
            data.push_back(file.readLine());
        }
        for(int i = 0;i < data.size();++i){
            qDebug()<<data[i];
        }
        file.close();
        return true;
    }
}

void MainWindow::prewrite(){
    data.clear();
}

void MainWindow::write(QString line){
    data.push_back(line);
}

void MainWindow::save(){
    QFile file(path);
    if(file.open(QIODevice::WriteOnly)){
        qDebug() <<"save: File save success!"<<endl;
        QTextStream out(&file);
        for(int i = 0;i < data.size();++i){
            out<<data[i];
        }
        file.close();
    }else{
        qDebug() <<"save: File save error!"<<endl;
    }
}

void MainWindow::saveas(){
    QString filename = "new file.txt";
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),"/Desktop",QFileDialog::ShowDirsOnly| QFileDialog::DontResolveSymlinks);
    QDir d;
    d.mkpath(dir);
    QFile file2(dir+"/"+filename);
    file2.open(QIODevice::WriteOnly);
    QTextStream out(&file2);
    for(int i = 0;i < data.size();++i){
        out<<data[i];
    }
    file2.close();
    qDebug()<<"saveas: File save success!"<<endl;
}

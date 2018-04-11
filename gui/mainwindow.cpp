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
#include <QKeyEvent>
#include <QKeySequence>
#include <QString>
#include "mainwindow.h"
#include "screen_cache.h"
using namespace std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setWindowTitle(tr("MiniWord"));
    this->setFixedSize(800,600);
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

    //输入框部分
    Input.setParent(this);
    Input.setGeometry(0,560,800,21);
    Input.show();
    Input.setEchoMode(QLineEdit::Normal);
    Input.setPlaceholderText("type...");
    Input.setReadOnly(1);

    for (int i = 0; i < ROW_NUMBER; ++i) {
        QLabel *pLabel = new QLabel(this);
        pLabel->setText(QString::number(i + 1));
        pLabel->setStyleSheet("color: black");
        pLabel->setGeometry(TEXT_LEFT_BLANK,
                            TEXT_UPPER_BLANK + LINE_HIGHT * i,
                            LINE_WIDTH,
                            LINE_HIGHT);
        screen_data_.append(pLabel);
    }


   /* QToolBar *toolBar = addToolBar(tr("&File"));
    toolBar->setToolTip("hello");
    toolBar->addAction(openAction);
    */
    statusBar();
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
            data.push_back(QString::fromLocal8Bit(file.readLine()));
        }
        for(int i = 0;i < data.size();++i){
            qDebug()<<data[i];
        }
        file.close();
        return true;
    }
}

QString MainWindow::read(int row){
    if(row >= data.size())
        return "";
    else
        return data[row];
}

void MainWindow::prewrite(){
    data.clear();
}

void MainWindow::write(QString line){
    data.push_back(line.toLocal8Bit());
}

void MainWindow::save(){
    QFile file(path);
    if(file.open(QIODevice::WriteOnly)){
        qDebug() <<"save: File save success!"<<endl;
        QTextStream out(&file);
        for(int i = 0; i < data.size(); ++i){
            out<<data[i];
        }
        file.close();
    }else{
        qDebug() <<"save: File save error!"<<endl;
    }
}

void MainWindow::saveas(){
    statusBar()->showMessage("保存中...");
    QString FileName = "Name.text()";
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),"/Desktop",QFileDialog::ShowDirsOnly| QFileDialog::DontResolveSymlinks);
    QDir d;
    d.mkpath(dir);
    QFile file2(dir+"/"+FileName);
    file2.open(QIODevice::WriteOnly);
    QTextStream out(&file2);
    for(int i = 0; i < data.size(); ++i){
        out<<data[i];
    }
    file2.close();
    qDebug()<<"saveas: File save success!"<<endl;
}

void MainWindow::RefreshScreen(ScreenCache screen_cache) {
    for (auto iter = screen_data_.begin(); iter != screen_data_.end(); ++iter) {
        (**iter).setText(QString::fromStdString(screen_cache.GetCacheIthLines(iter - screen_data_.begin())));
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event) {
    switch (event->key()) {
    case Qt::Key_1:
        Input.setReadOnly(0);
        Input.setPlaceholderText("typing...");
        break;
    }
}

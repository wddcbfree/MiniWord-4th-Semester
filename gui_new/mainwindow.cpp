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
#include <string>
#include <QTextStream>
#include <QDataStream>
#include <vector>
#include <QPushButton>
#include <QLabel>
#include <QPainter>
#include <QKeyEvent>
#include <QKeySequence>
#include <QString>
#include <QCloseEvent>
#include "mainwindow.h"
#include "file_process.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(tr("MiniWord"));
    this->setFixedSize(800,600);



    //菜单栏
    createAction = new QAction(tr("新文件"), this);
    createAction->setShortcuts(QKeySequence::New);
    createAction->setStatusTip(tr("Create a file"));
    //connect(createAction, &QAction::triggered, this, &MainWindow::precreate);

    openAction = new QAction(tr("打开..."), this);
    openAction->setShortcuts(QKeySequence::Open);
    openAction->setStatusTip(tr("Open an existing file"));
    connect(openAction, &QAction::triggered, this, &MainWindow::open);


    saveAction = new QAction(tr("保存"), this);
    saveAction->setShortcuts(QKeySequence::Save);
    saveAction->setStatusTip(tr("Save current file"));
    //connect(saveAction, &QAction::triggered, this, &MainWindow::save);

    saveasAction = new QAction(tr("另存为..."), this);
    saveasAction->setShortcuts(QKeySequence::SaveAs);
    saveasAction->setStatusTip(tr("Save as..."));
    //connect(saveasAction, &QAction::triggered, this, &MainWindow::saveas);

    QMenu *file = menuBar()->addMenu(tr("&文件"));
    file->addAction(createAction);
    file->addSection("");
    file->addAction(openAction);
    file->addAction(saveAction);
    file->addAction(saveasAction);
    QMenu *edit = menuBar()->addMenu(tr("&编辑"));
    QMenu *info = menuBar()->addMenu(tr("&关于"));
    info->addSection("hello");
/*
    //输入框部分
    Input.setParent(this);
    Input.setGeometry(0,560,800,21);
    Input.show();
    Input.setEchoMode(QLineEdit::Normal);
    Input.setPlaceholderText("type...");
    Input.setReadOnly(1);

    //输入提示
    InputTips.setParent(this);
    InputTips.setGeometry(2,540,800-1*2,21);
    InputTips.show();
    InputTips.setText("test");

    InitiateSceen();
*/
    //状态栏
    statusBar();
}

MainWindow::~MainWindow()
{

}

void MainWindow::open(){
    QString FilePath = QFileDialog::getOpenFileName(this,tr("打开..."));
    qDebug()<<FilePath<<endl;
    emit SendPath(FilePath);
}

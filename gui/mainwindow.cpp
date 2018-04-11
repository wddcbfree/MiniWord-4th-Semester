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
#include <QPainter>
#include <QKeyEvent>
#include <QKeySequence>
#include <QString>
#include <QCloseEvent>
#include "mainwindow.h"
#include "screen_cache.h"
using namespace std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setWindowTitle(tr("MiniWord"));
    this->setFixedSize(800,600);
    //菜单栏
    createAction = new QAction(tr("新文件"), this);
    createAction->setShortcuts(QKeySequence::New);
    createAction->setStatusTip(tr("Create a file"));
    connect(createAction, &QAction::triggered, this, &MainWindow::precreate);

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
    connect(saveasAction, &QAction::triggered, this, &MainWindow::pre_saveas);

    QMenu *file = menuBar()->addMenu(tr("&文件"));
    file->addAction(createAction);
    file->addSection("");
    file->addAction(openAction);
    file->addAction(saveAction);
    file->addAction(saveasAction);
    QMenu *edit = menuBar()->addMenu(tr("&编辑"));
    QMenu *info = menuBar()->addMenu(tr("&关于"));
    info->addSection("hello");

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

    //状态栏
    statusBar();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QMessageBox msgBox;
    msgBox.setText(tr("还有未保存的修改，确认退出？"));
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard);
    msgBox.setButtonText(QMessageBox::Save,"保存");
    msgBox.setButtonText(QMessageBox::Discard,"不保存");
    msgBox.setDefaultButton(QMessageBox::Save);
    int ret = msgBox.exec();
    switch (ret) {
    case QMessageBox::Save:
        save();
        qDebug() << "保存！";
        break;
    case QMessageBox::Discard:
        qDebug() << "不保存!";
        break;
    }
}

MainWindow::~MainWindow()
{

}

void MainWindow::precreate(){
    statusBar()->showMessage("创建文件中...");
    InputTips.setText("请输入要创建的文件名(含扩展名)，按回车结束：");
    Input.setReadOnly(0);
    Input.setPlaceholderText("*.txt");
    connect(&Input,&QLineEdit::returnPressed,this,&MainWindow::create);
}

void MainWindow::create(){
    QString FileName = Input.text();
    Input.clear();
    Input.setReadOnly(1);
    QString dir = QFileDialog::getExistingDirectory(this, tr("创建在..."),"/",QFileDialog::ShowDirsOnly| QFileDialog::DontResolveSymlinks);
    QDir d;
    d.mkpath(dir);
    path = dir+"/"+FileName;
    statusBar()->showMessage("创建成功！");
    InputTips.setText("");
    Input.setReadOnly(1);
    Input.setPlaceholderText("");
    qDebug()<<"create: File create success!"<<endl;
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
            a.AddStringEnd(file.readLine().toStdString());
        }
        for(int i = 0;i < data.size();++i){
            qDebug()<<data[i];
        }
        file.close();
        InitiateSceen();
        return true;
    }
}

/*QString MainWindow::read(int row){
    if(row >= data.size())
        return "";
    else
        return data[row];
}*/

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
        for(int i = 0; i < data.size(); ++i){
            out<<data[i];
        }
        file.close();
    }else{
        qDebug() <<"save: File save error!"<<endl;
    }
}

void MainWindow::pre_saveas(){
    statusBar()->showMessage("保存中...");
    InputTips.setText("请输入要保存的文件名(含扩展名)，按回车结束：");
    Input.setReadOnly(0);
    Input.setPlaceholderText("*.txt");
    connect(&Input,&QLineEdit::returnPressed,this,&MainWindow::saveas);
}

void MainWindow::saveas(){
    QString FileName = Input.text();
    Input.clear();
    Input.setReadOnly(1);
    QString dir = QFileDialog::getExistingDirectory(this, tr("另存在..."),"/",QFileDialog::ShowDirsOnly| QFileDialog::DontResolveSymlinks);
    QDir d;
    d.mkpath(dir);
    QFile file2(dir+"/"+FileName);
    file2.open(QIODevice::WriteOnly);
    QTextStream out(&file2);
    for(int i = 0; i < data.size(); ++i){
        out<<data[i];
    }
    file2.close();
    statusBar()->showMessage("保存成功！");
    InputTips.setText("");
    Input.setReadOnly(1);
    Input.setPlaceholderText("");
    qDebug()<<"saveas: File save success!"<<endl;
}

void MainWindow::InitiateSceen(){
    for (int i = 0; i < ROW_NUMBER; ++i) {
        QLabel *pLabel = new QLabel(this);
        pLabel->setText(QString::number(i + 1));
        pLabel->setStyleSheet("color: black");
        pLabel->setGeometry(TEXT_LEFT_BLANK,
                            TEXT_UPPER_BLANK + LINE_HIGHT * i,
                            LINE_WIDTH,
                            LINE_HIGHT);
        pLabel->show();
        screen_data_.append(pLabel);
    }
}

void MainWindow::RefreshScreen(ScreenCache screen_cache) {
    for (auto iter = screen_data_.begin(); iter != screen_data_.end(); ++iter) {
        (**iter).setText(QString::fromStdString(screen_cache.GetCacheIthLines(iter - screen_data_.begin())));
    }
}

void MainWindow::getInputText(){
    InputText = Input.text();
}

void MainWindow::keyReleaseEvent(QKeyEvent *event) {
    switch (event->key()) {
    case Qt::Key_1:
        Input.setReadOnly(0);
        Input.setPlaceholderText("typing...");
        break;
    //default:
        //break;
    }
}

void MainWindow::paintEvent(QPaintEvent *)
{
    //分割线
    QPainter LineDrawer(this);
    LineDrawer.setPen(QPen(Qt::gray,1));
    LineDrawer.drawLine(0,540,800,540);
}


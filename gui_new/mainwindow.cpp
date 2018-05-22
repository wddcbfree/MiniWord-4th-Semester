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

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(tr("MiniWord"));
    this->setFixedSize(WINDOW_WIDTH,WINDOW_HEIGHT);

    //菜单栏
    createAction = new QAction(tr("新文件"), this);
    createAction->setShortcuts(QKeySequence::New);
    createAction->setStatusTip(tr("Create a file"));
    connect(createAction, &QAction::triggered, this, &MainWindow::create);

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
    connect(saveasAction, &QAction::triggered, this, &MainWindow::save_as);

    quitAction = new QAction(tr("退出"),this);
    quitAction->setShortcuts(QKeySequence::Quit);
    quitAction->setStatusTip(tr("Quit"));
    connect(quitAction,&QAction::triggered,this,&MainWindow::close);

    searchAction = new QAction(tr("查找..."),this);
    searchAction->setShortcuts(QKeySequence::Find);
    searchAction->setStatusTip(tr("Search..."));
    connect(searchAction,&QAction::triggered,this,&MainWindow::search);

    replaceAction = new QAction(tr("替换"),this);
    replaceAction->setShortcuts(QKeySequence::Replace);
    replaceAction->setStatusTip(tr("Replace"));
    connect(replaceAction,&QAction::triggered,this,&MainWindow::search);

    selectAction = new QAction(tr("选中块"),this);
    selectAction->setStatusTip(tr("Select"));

    QMenu *file = menuBar()->addMenu(tr("&文件"));
    file->addAction(createAction);
    file->addSection("");
    file->addAction(openAction);
    file->addAction(saveAction);
    file->addAction(saveasAction);
    file->addSection("");
    file->addAction(quitAction);
    QMenu *edit = menuBar()->addMenu(tr("&编辑"));
    edit->addAction(searchAction);
    edit->addAction(replaceAction);
    edit->addSection("");
    edit->addAction(selectAction);
    QMenu *info = menuBar()->addMenu(tr("&关于"));
    //info->addAction(aboutRole);

    //输入框部分
    Input.setParent(this);
    Input.setGeometry(INPUT_LEFT_BLANK,WINDOW_HEIGHT-2*LINE_HEIGHT,WINDOW_WIDTH-2*INPUT_LEFT_BLANK,LINE_HEIGHT);
    Input.show();
    Input.setEchoMode(QLineEdit::Normal);
    Input.setPlaceholderText("type...");
    Input.setReadOnly(1);
    Input.setAcceptDrops(true);
    Input.setClearButtonEnabled(true);
    connect(&Input,&QLineEdit::returnPressed,this,&MainWindow::input_return_pressed);

    //输入提示
    InputTips.setParent(this);
    InputTips.setGeometry(INPUT_LEFT_BLANK,WINDOW_HEIGHT-3*LINE_HEIGHT,WINDOW_WIDTH-2*INPUT_LEFT_BLANK,LINE_HEIGHT);
    InputTips.show();
    InputTips.setText("test");

 //   InitiateSceen();

    //状态栏
    statusBar();
}

MainWindow::~MainWindow()
{

}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(filepart->is_edited()){
        QMessageBox msgBox;
        msgBox.setText(tr("还有未保存的修改，是否保存？"));
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
    filepart->clearData();
}

void MainWindow::create(){
    if(!filepart->is_edited()){
        QMessageBox msgBox;
        msgBox.setText(tr("还有未保存的修改，是否保存？"));
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
    emit SendCreateSignal();
}

void MainWindow::open(){
    QString FilePath = QFileDialog::getOpenFileName(this,tr("打开..."));
    qDebug()<<FilePath<<endl;
    emit SendOpenPath(FilePath);
    statusBar()->showMessage("打开成功！");
}

void MainWindow::save(){
    if(filepart->is_open()){
        QString FilePath;
        if(filepart->is_create()){
            FilePath = QFileDialog::getSaveFileName(this,tr("保存为..."),"新建文档.txt");
        }
        emit SendSavePath(FilePath);
        statusBar()->showMessage("保存成功！");
    }
}

void MainWindow::save_as(){
    QString FilePath = QFileDialog::getSaveFileName(this,tr("另存为..."),"新建文档.txt");
    emit SendSaveAsPath(FilePath);
}

void MainWindow::keyReleaseEvent(QKeyEvent *event) {
    switch (event->key()) {
    case Qt::Key_1:
        Input.setReadOnly(0);
        Input.setPlaceholderText("typing...");
        break;
    //case Qt::Key_Delete:
    //default:
        //break;
    }
}

void MainWindow::input_return_pressed(){
    qDebug()<<"return success!";
    /*if(Input.size() == 0)
        //插入空行
    else
        //插入现有数据，然后清空*/
}

void MainWindow::search(){
    QDialog SearchDialog(this);
    SearchDialog.setSizeIncrement(410,4*LINE_HEIGHT);
    SearchDialog.setWindowTitle("查找");
    SearchDialog.setModal(0);
    QLineEdit SearchInput(&SearchDialog),ReplaceInput(&SearchDialog);
    SearchInput.setGeometry(INPUT_LEFT_BLANK,LINE_GAP,200-2*INPUT_LEFT_BLANK,LINE_HEIGHT);
    SearchInput.setPlaceholderText("输入要查找的内容...");
    ReplaceInput.setGeometry(210+INPUT_LEFT_BLANK,LINE_GAP,200-2*INPUT_LEFT_BLANK,LINE_HEIGHT);
    ReplaceInput.setPlaceholderText("替换为...");
    QPushButton Search(&SearchDialog),SearchNext(&SearchDialog),Replace(&SearchDialog);
    Search.setGeometry(INPUT_LEFT_BLANK,2*LINE_GAP+LINE_HEIGHT,200-2*INPUT_LEFT_BLANK,LINE_HEIGHT);
    Search.setText("查找");
    Search.setStyleSheet("color:black");
    SearchNext.setGeometry(INPUT_LEFT_BLANK,3*LINE_GAP+2*LINE_HEIGHT,200-2*INPUT_LEFT_BLANK,LINE_HEIGHT);
    SearchNext.setText("下一个");
    Replace.setGeometry(210+INPUT_LEFT_BLANK,2*LINE_GAP+LINE_HEIGHT,200-2*INPUT_LEFT_BLANK,LINE_HEIGHT);
    Replace.setText("替换");
    SearchDialog.exec();
}

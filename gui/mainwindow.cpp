#include <QAction>
#include <QMenuBar>
#include <QMessageBox>
#include <QStatusBar>
#include <QToolBar>

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setWindowTitle(tr("MiniWord"));

    openAction = new QAction(tr("打开..."), this);
    openAction->setShortcuts(QKeySequence::Open);
    //openAction->setStatusTip(tr("Open an existing file"));
    connect(openAction, &QAction::triggered, this, &MainWindow::open);

    QMenu *file = menuBar()->addMenu(tr("&文件"));
    file->addAction(openAction);

   /* QToolBar *toolBar = addToolBar(tr("&File"));
    toolBar->setToolTip("hello");
    toolBar->addAction(openAction);
    */
    statusBar() ;
}

MainWindow::~MainWindow()
{
}

void MainWindow::open()
{
    QMessageBox::information(this,tr("information"),tr("Open"));
}

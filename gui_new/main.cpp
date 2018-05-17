#include "mainwindow.h"
#include "file_process.h"
#include <QApplication>
#include <QObject>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    FileProcess fileprocess;
    QObject::connect(&w,&MainWindow::SendPath,&fileprocess,&FileProcess::open_file);
    w.show();
    return a.exec();
}

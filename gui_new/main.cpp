#include "mainwindow.h"
#include "file_process.h"
#include "memory_new.h"
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    Text memory;
    FileProcess fileprocess;
    fileprocess.init_memory(&memory);
    w.init_memory(&memory);
    w.init_file(&fileprocess);

    QObject::connect(&w, &MainWindow::SendOpenPath, &fileprocess, &FileProcess::open_file);
    QObject::connect(&w, &MainWindow::SendCreateSignal, &fileprocess, &FileProcess::create_file);
    QObject::connect(&w, &MainWindow::SendSavePath, &fileprocess, &FileProcess::save_file);
    QObject::connect(&w, &MainWindow::SendSaveAsPath, &fileprocess, &FileProcess::save_as);

    w.show();
    return a.exec();
}

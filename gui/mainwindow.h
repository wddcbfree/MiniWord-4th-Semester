#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    void open();
    void create();

    QAction *openAction;
    QAction *saveAction;
    QAction *createAction;
};

#endif // MAINWINDOW_H

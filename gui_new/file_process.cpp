#include "file_process.h"
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

void FileProcess::open_file(QString path){
    qDebug()<<"I'm here~"<<endl;
    QFile file(path);
    if(!file.open(QFile::ReadOnly|QFile::Text)){
        qDebug()<<"open(): file open error!"<<endl;
        file.close();
    }else{
        qDebug()<<"open(): file open success!"<<endl;
        data.clear();
        while(!file.atEnd()){
            data.push_back(file.readLine().toStdString());
        }
        //for(int i = 0;i < data.size();++i)
          //  qDebug()<<data[i];
        file.close();
    }
}

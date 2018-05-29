#pragma once
#ifndef SCREEN_
#define SCREEN_

#include <QLabel>
#include <string>
#include <QString>
#include <QVector>
#include <QMainWindow>
#include "memory_new.h"

struct CursorPosition{
    int column = 0;
    int row = 0;
};

class Screen{
public:
    void InitiateScreen(QMainWindow *qmainwindow);
    void LoadScreen(Text text);
    void DisplayScreen();
private:
    void RefreshScreenPosition(Text text);
    int GetLetterNumber(QString str);
    QVector<QString> screen_data_;
    QVector<QLabel*> screen_display_;
    struct CursorPosition relative_position_, screen_position_;
    int cursor_display_count = 0;
};

#endif //SCREEN_

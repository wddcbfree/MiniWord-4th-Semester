#pragma once
#ifndef SCREEN_
#define SCREEN_

#include <Qlabel>
#include <string>
#include <Qstring>
#include <Qvector>
#include <QMainWindow>
#include "memory_new.h"

struct SursorPosition{
    int column = 0;
    int raw = 0;
};

class Screen{
public:
    void InitiateScreen(QMainWindow *qmainwindow);
    void LoadScreen(Text text);
    void DisplayScreen();
private:
    QVector<QString> screen_data_;
    QVector<QLabel*> screen_display_;
    struct SursorPosition relative_position_, screen_position_;
    int cursor_display_count = 0;
};

#endif //SCREEN_

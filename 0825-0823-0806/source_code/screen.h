#pragma once
#ifndef SCREEN_
#define SCREEN_

#include <QLabel>
#include <QString>
#include <QVector>
#include <QMainWindow>
#include "memory_new.h"

struct CursorPosition {
    int column = 0;
    int row = 0;
};

class Screen {
public:
    void InitiateScreen(QMainWindow *qmainwindow);
    void LoadScreen(Text text);
    void DisplayScreen();
    void HighlightMode(int, int, int, int);
    void CursorMode();
private:
    void RefreshScreenPosition(Text text);
    int GetLetterNumber(QString str) const;
    struct CursorPosition AdjustHighlightCursor(const struct CursorPosition);
    QVector<QString> screen_data_;
    QVector<QLabel*> screen_display_;
    struct CursorPosition relative_position_;
    struct CursorPosition screen_position_;
    struct CursorPosition highlight_start_;
    struct CursorPosition highlight_end_;
    int display_mode_ = CURSOR_MODE;
    int cursor_display_count_ = 0;
};

#endif //SCREEN_

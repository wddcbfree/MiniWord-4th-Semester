#pragma once
#ifndef SCREEN_
#define SCREEN_

#include <Qlable>
#include <string>
#include <Qstring>
#include <Qvector>
#include <memory.h>

#define DISPLAY_COUNT 30

struct SursorPosition{
    int column = 0;
    int raw = 0;
}

class Screen{
public:
    void InitiateScreen();
    void LoadScreen();
    void DisplayScreen();
private:
    Qvector<Qstring> screen_text_;
    Qvector<Qlable *> screen_display_;
    struct SursorPosition truth_position_, relative_position_, screen_position_;
    bool cursor_display_flag = 0;
    int cursor_display_count = 0;
};

#endif //SCREEN_
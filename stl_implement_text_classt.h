#pragma once
#ifndef STL_IMPLEMENT_TEXT_CLASS_
#define STL_IMPLEMENT_TEXT_CLASS_

#include <string>
#include <vector>

class STLTest {
public:
    void AddStringEnd(const std::string &add_string_end);
    void InsertString(const std::string &insert_string);
    void InputEnter();
    void InputBackspace();
    void DeleteEntireLine();
    void TakePlaceString(const std::string &search_word, const std::string &take_place);
    void ConfirmTakePlace(bool confirm_take_place);
    void SearchWord(const std::string &search_word);
    std::string GetIthString(int ith);
    ScreenInfo GetPosition();
private:
    std::vector<std::string> test_;
    ScreenInfo screen_info_;
};

struct ScreenInfo {
    int cursor_x;   //cursor position
    int cursor_y;
    int screen_x;   //screen left-up position
    int screen_y;
};

#endif // !STL_IMPLEMENT_TEXT_CLASS_

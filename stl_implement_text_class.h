#pragma once
#ifndef STL_IMPLEMENT_TEXT_CLASS_
#define STL_IMPLEMENT_TEXT_CLASS_

#define WINDOWS_HIGHT 80
#define WINDOWS_WIDTH 150

#include <string>
#include <vector>

struct ScreenInfo {
    int cursor_x;   //cursor position
    int cursor_y;
    int screen_x;   //screen left-up position
    int screen_y;
};

class Text {
public:
    void AddStringEnd(const std::string &add_string_end);
    void InsertString(const std::string &insert_string);
    void DeleteForward();
    void DeleteBackward();
    void DeleteEntireLine();
    void MoveUp();
    void MoveDown();
    void MoveRight();
    void MoveLeft();
    bool SearchWord(const std::string &search_word);
    void TakePlaceString(const std::string &search_word, const std::string &take_place);
    void ConfirmTakePlace(bool confirm_take_place);
    void FreshScreenPosition();
    int GetNumOfLines();
    std::string GetIthString(int i);
    ScreenInfo GetPosition();
private:
    std::vector<std::string> text_;
    ScreenInfo screen_info_;
    std::string take_place_;
    int GetColumeNum_();
    int GetRowNum_();
};

#endif // !STL_IMPLEMENT_TEXT_CLASS_

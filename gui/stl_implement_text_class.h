#pragma once
#ifndef STL_IMPLEMENT_TEXT_CLASS_
#define STL_IMPLEMENT_TEXT_CLASS_

#define ROW_NUMBER 40
#define COLUME_NUMBER 150

#include <string>
#include <vector>
#include <iostream>

struct ScreenInfo {
    int cursor_x = 0;   //cursor position
    int cursor_y = 0;
    int screen_x = 0;   //screen left-up position
    int screen_y = 0;
};

class Text {
public:
    void AddStringEnd(const std::string &add_string_end);
    void ClearText();
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
    void RefreshScreenPosition();
    int GetNumOfLines();
    std::string GetIthString(int i);
    ScreenInfo GetPosition();
    void RefreshScreenCache();
    std::string GetIthCacheString(int i);
private:
    std::vector<std::string> text_;
    std::vector<std::string> cache_;
    ScreenInfo screen_info_;
    std::string take_place_;
    int GetColumeNum_();
    int GetRowNum_();
};

#endif // !STL_IMPLEMENT_TEXT_CLASS_

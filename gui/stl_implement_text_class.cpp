#include "stl_implement_text_class.h"

void Text::AddStringEnd(const std::string & add_string_end) {
    text_.push_back(add_string_end);
    return;
}

void Text::InsertString(const std::string & insert_string) {
    text_[GetRowNum_()].insert(GetColumeNum_(), insert_string);
    return;
}

void Text::DeleteForward() {
    if (GetColumeNum_() == 0) {
        DeleteEntireLine();
    }
    else {
        text_[GetColumeNum_()].erase(GetRowNum_(), 1);
        MoveLeft();
    }
    return;
}

void Text::DeleteBackward() {
    if (GetColumeNum_() == text_[GetRowNum_()].length()) {
        MoveRight();
        const std::string temp_next_line = text_[GetRowNum_()];
        DeleteEntireLine();
        MoveLeft();
        text_[GetRowNum_()] += temp_next_line;
    }
    else {
        text_[GetColumeNum_()].erase(GetRowNum_() + 1, 1);
    }
    return;
}

void Text::DeleteEntireLine() {
    text_.erase(text_.begin() + GetRowNum_());
    return;
}

void Text::MoveUp() {
    if (GetRowNum_() != 0) {
        --screen_info_.screen_y;
    }
    return;
}

void Text::MoveDown() {
    if (GetRowNum_() != GetNumOfLines()) {
        ++screen_info_.screen_y;
    }
    return;
}

void Text::MoveRight() {
    if (GetColumeNum_() == text_[GetRowNum_()].length() && GetRowNum_() != GetNumOfLines()) {
        ++screen_info_.cursor_y;
        screen_info_.cursor_x = 0;
    }
    else {
        ++screen_info_.cursor_x;
    }
    return;
}

void Text::MoveLeft() {
    if (GetColumeNum_() == 0 && GetRowNum_() != 0) {
        --screen_info_.cursor_y;
        screen_info_.cursor_x = static_cast<int>(text_[GetRowNum_()].length());
    }
    else {
        --screen_info_.cursor_x;
    }
}

bool Text::SearchWord(const std::string & search_word) {
    //search the word from the current position
    auto temp_search_position = text_[GetRowNum_()].find(search_word, GetColumeNum_());
    if (temp_search_position != std::string::npos) {
        screen_info_.cursor_x = static_cast<int>(temp_search_position) - screen_info_.screen_x;
        return true;
    }
    //search the word from next line
    for (auto i = text_.begin() + GetRowNum_(); i != text_.end(); ++i) {
        temp_search_position = i->find(search_word);
        if (temp_search_position != std::string::npos) {
            screen_info_.cursor_x = static_cast<int>(temp_search_position) - screen_info_.screen_x;
            screen_info_.cursor_y = static_cast<int>(i - text_.begin()) - screen_info_.screen_y;
            return true;
        }
    }
    return false;
}

void Text::TakePlaceString(const std::string & search_word, const std::string & take_place) {
    SearchWord(search_word);
    take_place_ = take_place;
    return;
}

void Text::ConfirmTakePlace(bool confirm_take_place) {
    if (confirm_take_place) {
        InsertString(take_place_);
    }
    take_place_.clear();
    return;
}

void Text::RefreshScreenPosition() {
    if (screen_info_.cursor_x > COLUME_NUMBER) {
        screen_info_.screen_x += screen_info_.cursor_x - COLUME_NUMBER ;
        screen_info_.cursor_x = COLUME_NUMBER;
    }
    if (screen_info_.cursor_x <= 0) {
        screen_info_.screen_x += screen_info_.cursor_x;
        screen_info_.cursor_x = 0;
    }
    if (screen_info_.cursor_y > ROW_NUMBER) {
        screen_info_.screen_x += screen_info_.cursor_y - ROW_NUMBER;
        screen_info_.cursor_y = ROW_NUMBER;
    }
    if (screen_info_.cursor_y <= 0) {
        screen_info_.screen_y += screen_info_.cursor_y;
        screen_info_.cursor_y = 0;
    }
    return;
}

int Text::GetNumOfLines() {
    return static_cast<int>(text_.end() - text_.begin());
}

std::string Text::GetIthString(int i) {
    return text_[i];
}

ScreenInfo Text::GetPosition() {
    return screen_info_;
}

void Text::RefreshScreenCache()
{
    cache_.clear();
    for (int i = 0; i <= ROW_NUMBER; ++i) {
        if (i + screen_info_.cursor_y < GetNumOfLines()) {
            cache_.push_back(GetIthString(i + screen_info_.cursor_y).substr(GetColumeNum_(), COLUME_NUMBER));
        } else {
            cache_.push_back(std::string());
        }
    }
}

std::string Text::GetIthCacheString(int i)
{
    return cache_[i];
}

int Text::GetColumeNum_() {
    return screen_info_.screen_x + screen_info_.cursor_x;
}

int Text::GetRowNum_() {
    return screen_info_.screen_y + screen_info_.cursor_y;
}

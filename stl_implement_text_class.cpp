#include "stl_implement_text_class.h"

void STLText::AddStringEnd(const std::string & add_string_end) {
    text_.push_back(add_string_end);
    return;
}

void STLText::InsertString(const std::string & insert_string) {
    text_[screen_info_.screen_y + screen_info_.cursor_y - 2].insert(screen_info_.cursor_x - 1, insert_string);
    return;
}

void STLText::DeleteForward() {
    text_[screen_info_.screen_y + screen_info_.cursor_y - 2].erase(screen_info_.cursor_x - 1, 1);
    return;
}

void STLText::DeleteBackward() {
    text_[screen_info_.screen_y + screen_info_.cursor_y - 2].erase(screen_info_.cursor_x, 1);
    return;
}

void STLText::DeleteEntireLine() {
    text_.erase(text_.begin() + screen_info_.screen_y + screen_info_.cursor_y - 2);
    return;
}

void STLText::MoveUp() {
    if (screen_info_.screen_y + screen_info_.cursor_y - 2 != 0) {
        --screen_info_.screen_y;
    }
    return;
}

void STLText::MoveDown() {
    if (screen_info_.screen_y + screen_info_.cursor_y - 2 != text_.end() - text_.begin()) {
        ++screen_info_.screen_y;
    }
    return;
}

void STLText::MoveRight() {
    if (screen_info_.cursor_x != text_[screen_info_.screen_y + screen_info_.cursor_y - 2].length()) {
        ++screen_info_.cursor_x;
    }
    return;
}

void STLText::MoveLeft() {
    if (screen_info_.cursor_x != 1) {
        --screen_info_.cursor_x;
    }
}

void STLText::SearchWord(const std::string & search_word) {
    auto temp_search_position = text_[screen_info_.screen_y + screen_info_.cursor_y - 2].find(search_word, screen_info_.cursor_x - 1);
    if (temp_search_position != std::string::npos) {
        screen_info_.cursor_x = static_cast<int>(temp_search_position);
        return;
    }
    for (auto i = text_.begin() + screen_info_.screen_y + screen_info_.cursor_y - 1; i != text_.end(); ++i) {
        temp_search_position = i->find(search_word);
        if (temp_search_position != std::string::npos) {
            screen_info_.cursor_x = static_cast<int>(temp_search_position);
            return;
        }
    }
    return;
}

void STLText::TakePlaceString(const std::string & search_word, const std::string & take_place) {
    SearchWord(search_word);
    take_place_ = take_place;
    return;
}

void STLText::ConfirmTakePlace(bool confirm_take_place) {
    if (confirm_take_place) {
        InsertString(take_place_);
    }
    take_place_.clear();
    return;
}

int STLText::GetNumOfLines() {
    return text_.end() - text_.begin();
}

std::string STLText::GetIthString(int ith) {
    return text_[ith - 1];
}

ScreenInfo STLText::GetPosition() {
    return screen_info_;
}

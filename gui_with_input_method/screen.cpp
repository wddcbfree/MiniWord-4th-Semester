#include "screen.h"
#include <algorithm>
#include <QDebug>

void Screen::InitiateScreen(QMainWindow *qmainwindow) {
    for (int i = 0; i < ROW_NUMBER; ++i) {
        QLabel *pLabel = new QLabel(qmainwindow);
        QFont ft;
        ft.setPointSize(FONT_SIZE);
        pLabel->setFont(ft);
        pLabel->setText("");
        pLabel->setStyleSheet("color: black");
        pLabel->setGeometry(TEXT_LEFT_BLANK,
            TEXT_UPPER_BLANK + (LINE_HEIGHT + LINE_GAP) * i,
            LINE_WIDTH,
            LINE_HEIGHT);
        pLabel->show();
        screen_display_.append(pLabel);
        screen_data_.push_back("");
    }
    return;
}

void Screen::LoadScreen(Text text) {
        RefreshScreenPosition(text);
    screen_data_.clear();
    const auto lines_number = text.GetNumOfLines();
    for (int i = 0; i < ROW_NUMBER; ++i) {
        if (i + screen_position_.row < lines_number && screen_position_.column < text.GetIthString(i + screen_position_.row).length()) {
            QString temp_text = text.GetIthString(i + screen_position_.row);
            temp_text = temp_text.mid(screen_position_.column, GetLetterNumber(temp_text));
            screen_data_.push_back(temp_text);
        }
        else {
            screen_data_.push_back(QString(""));
        }
    }
    return;
}

void Screen::DisplayScreen() {
    cursor_display_count_ = (cursor_display_count_ + 1) % (DISPLAY_COUNT << 1);
    const auto start = AdjustHighlightCursor(highlight_start_);
    const auto end = AdjustHighlightCursor(highlight_end_);
    for (auto iter = screen_display_.begin(); iter != screen_display_.end(); ++iter) {
        auto temp_str = screen_data_[iter - screen_display_.begin()];
        const int cur_row_num = iter - screen_display_.begin();
        if (display_mode_ == HIGHLIGHT_MODE) {
            if (start.row == end.row && start.row == cur_row_num) {
                temp_str.insert(end.column, "</span>");
                temp_str.insert(start.column, "<span style=\"background-color:#b1d8fe\">");
                qDebug() << temp_str;
            }
            else {
                if (cur_row_num == start.row) {
                    temp_str += " </span>";
                    temp_str.insert(start.column, "<span style=\"background-color:#b1d8fe\">");
                }
                if (cur_row_num == end.row) {
                    temp_str.insert(end.column, "</span>");
                    temp_str = "<span style=\"background-color:#b1d8fe\">" + temp_str;
                }
                if (start.row < cur_row_num && cur_row_num < end.row) {
                    temp_str = "<span style=\"background-color:#b1d8fe\">" + temp_str + " </span>";
                }
            }
        }
       if (display_mode_ == CURSOR_MODE) {
            if (cursor_display_count_ < DISPLAY_COUNT && iter - screen_display_.begin() == relative_position_.row) {
                temp_str.insert(relative_position_.column + 1, "</span>");
                temp_str.insert(relative_position_.column, "<span style=\"background-color:#000000\">");
            }
        }
        //qDebug() << temp_str;
        (**iter).setText("<span style=\"background-color:#ffffff\"><pre>" + temp_str + "</pre></span>");
        (**iter).show();
    }
    return;
}

void Screen::RefreshScreenPosition(Text text) {
    cursor_display_count_ = 0;
    struct CursorPosition truth_position;
    truth_position.column = text.GetCursorCol();
    truth_position.row = text.GetCursorRow();
    relative_position_.column = truth_position.column - screen_position_.column;
    relative_position_.row = truth_position.row - screen_position_.row;
    const auto temp_str = text.GetIthString(truth_position.row);
    while (relative_position_.column >= GetLetterNumber(temp_str)) {
        screen_position_.column += 1;
        relative_position_.column -= 1;
    }
    if (relative_position_.column < 0) {
        screen_position_.column += relative_position_.column;
        relative_position_.column = 0;
    }
    if (relative_position_.row >= ROW_NUMBER) {
        screen_position_.row += relative_position_.row - ROW_NUMBER + 1;
        relative_position_.row = ROW_NUMBER - 1;
    }
    if (relative_position_.row < 0) {
        screen_position_.row += relative_position_.row;
        relative_position_.row = 0;
    }
    return;
}

int Screen::GetLetterNumber(QString str) const {
    int number = 0;
    double length = 0;
    if (str.length() > screen_position_.column) {
        str = str.right(str.length() - screen_position_.column);
        while (length < COLUME_NUMBER && str.length()) {
            const auto letter = (str[0]).unicode();
            if (letter >= 0x4E00 && letter <= 0x9FA5) {
                length += 0.6;
            }
            length += 1;
            ++number;
            str = str.right(str.length() - 1);
        }
    }
    number += static_cast<int>(COLUME_NUMBER - length);
    return number;
}

CursorPosition Screen::AdjustHighlightCursor(const CursorPosition original) {
    auto fixed_cursor = original;
    if (fixed_cursor.row < screen_position_.row) {
        fixed_cursor.row = screen_position_.row;
        fixed_cursor.column = screen_position_.column;
    }
    if (fixed_cursor.column < screen_position_.column) {
        fixed_cursor.column = screen_position_.column;
    }
    if (fixed_cursor.row > screen_position_.row + ROW_NUMBER - 1) {
        fixed_cursor.row = screen_position_.row + ROW_NUMBER - 1;
        fixed_cursor.column = screen_position_.column + screen_data_[fixed_cursor.row - screen_position_.row].length();
    }
    if (fixed_cursor.column > screen_position_.column + screen_data_[fixed_cursor.row - screen_position_.row].length()) {
        fixed_cursor.column = screen_position_.column + screen_data_[fixed_cursor.row - screen_position_.row].length();
    }
    fixed_cursor.row -= screen_position_.row;
    fixed_cursor.column -= screen_position_.column;
    return fixed_cursor;
}

void Screen::HighlightMode(int row_start, int col_start, int row_end, int col_end) {
    display_mode_ = HIGHLIGHT_MODE;
    highlight_start_.row = row_start;
    highlight_start_.column = col_start;
    highlight_end_.row = row_end;
    highlight_end_.column = col_end;
    if (highlight_start_.row > highlight_end_.row || (highlight_start_.row == highlight_end_.row && highlight_start_.column > highlight_end_.column)) {
        std::swap(highlight_start_, highlight_end_);
    }
    qDebug() << row_start << ' ' << col_start << ' ' << row_end << ' ' << col_end;
    return;
}
void Screen::CursorMode() {
    display_mode_ = CURSOR_MODE;
    return;
}

#include "screen.h"
#include <algorithm>
#include <QDebug>

void Screen::InitiateScreen(QMainWindow *qmainwindow) {
    for (int i = 0; i < ROW_NUMBER; ++i) {
        QLabel *pLabel = new QLabel(qmainwindow);
        pLabel->installEventFilter(qmainwindow);
        QFont ft;
        ft.setPointSize(FONT_SIZE);
        pLabel->setFont(ft);
        pLabel->setText(QString::number(i + 1));
        pLabel->setStyleSheet("color: black");
        pLabel->setGeometry(TEXT_LEFT_BLANK,
                            TEXT_UPPER_BLANK + (LINE_HEIGHT + LINE_GAP) * i,
                            LINE_WIDTH,
                            LINE_HEIGHT);
        pLabel->show();
        screen_display_.append(pLabel);
        screen_data_.push_back(QString::number(i + 1));
    }
    return;
}

void Screen::LoadScreen(Text text) {
    RefreshScreenPosition(text);
    screen_data_.clear();
    auto lines_number = text.GetNumOfLines();
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
    for (auto iter = screen_display_.begin(); iter != screen_display_.end(); ++iter) {
        QString temp_str = screen_data_[iter - screen_display_.begin()];
        if (highlight_mode_) {
            if (highlight_start_.row == highlight_end_.row && highlight_start_.row - screen_position_.row == iter - screen_display_.begin()) {
                temp_str.insert(highlight_end_.column - screen_position_.column + 1, "</span>");
                temp_str.insert(highlight_start_.column - screen_position_.column, "<span style=\"background-color:#b1d8fe\">");
            }
        }
        else {
            if (cursor_display_count_ < DISPLAY_COUNT && iter - screen_display_.begin() == relative_position_.row) {
                temp_str.insert(relative_position_.column + 1, "</span>");
                temp_str.insert(relative_position_.column, "<span style=\"background-color:#000000\">");
            }
        }
        //qDebug() << temp_str;
        (**iter).setText("<span style=\"background-color:#ffffff\"><pre>" + temp_str + " </pre></span>");
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
    QString temp_str = text.GetIthString(truth_position.row);
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

int Screen::GetLetterNumber(QString str) {
    int number = 0;
    double length = 0;
    if (str.length() > screen_position_.column) {
        str = str.right(str.length() - screen_position_.column);
        while (length < COLUME_NUMBER && str.length()) {
            auto letter = (str[0]).unicode();
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

void Screen::HighlightMode(int row_start, int col_start, int row_end, int col_end) {
    highlight_mode_ = true;
    highlight_start_.row = row_start;
    highlight_start_.column = col_start;
    highlight_end_.row = row_end;
    highlight_end_.column = col_end;
    if (highlight_start_.row > highlight_end_.row || (highlight_start_.row == highlight_end_.row && highlight_start_.column > highlight_end_.column)) {
        std::swap(highlight_start_, highlight_end_);
    }
    return;
}
void Screen::CursorMode() {
    highlight_mode_ = false;
    return;
}

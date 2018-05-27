#include "screen.h"

void Screen::InitiateScreen(QMainWindow *qmainwindow) {
    for (int i = 0; i < ROW_NUMBER; ++i) {
        QLabel *pLabel = new QLabel(qmainwindow);
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
            QString temp_text = QString::fromStdString(text.GetIthString(i + screen_position_.row).substr(screen_position_.column, COLUME_NUMBER));
            /*
            if (temp_text == "\u0000") {
                temp_text = " ";
            }
            */
            screen_data_.push_back(temp_text);
        }
        else {
            screen_data_.push_back(QString(""));
        }
    }
    return;
}

void Screen::DisplayScreen() {
    cursor_display_count = (cursor_display_count + 1) % (DISPLAY_COUNT << 1);
    for (auto iter = screen_display_.begin(); iter != screen_display_.end(); ++iter) {
        QString temp_str = screen_data_[iter - screen_display_.begin()];
        if (cursor_display_count < DISPLAY_COUNT && iter - screen_display_.begin() == relative_position_.row) {
            temp_str.insert(relative_position_.column + 1, "</span>");
            temp_str.insert(relative_position_.column, "<span style=\"background-color:#000000\">");

        }
        (**iter).setText("<span style=\"background-color:#FFFFFF\"><pre>" + temp_str + "</pre></span>");
        //(**iter).setText(temp_str);
        (**iter).show();
    }
    return;
}

void Screen::RefreshScreenPosition(Text text) {
    cursor_display_count = 0;
    struct CursorPosition truth_position;
    truth_position.column = text.GetCursorCol();
    truth_position.row = text.GetCursorRow();
    relative_position_.column = truth_position.column - screen_position_.column;
    relative_position_.row = truth_position.row - screen_position_.row;
    if (relative_position_.column >= COLUME_NUMBER) {
        screen_position_.column += relative_position_.column - COLUME_NUMBER + 1;
        relative_position_.column = COLUME_NUMBER - 1;
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

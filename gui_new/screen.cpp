#include "screen.h"

void Screen::InitiateScreen(QMainWindow *qmainwindow) {
    for (int i = 0; i < ROW_NUMBER; ++i) {
        QLabel *pLabel = new QLabel(qmainwindow);
        pLabel->setText(QString::number(i + 1));
        pLabel->setStyleSheet("color: black");
        pLabel->setGeometry(TEXT_LEFT_BLANK,
                            TEXT_UPPER_BLANK + (LINE_GAP + LINE_HEIGHT) * i,
                            LINE_WIDTH,
                            LINE_HEIGHT);
        pLabel->show();
        screen_display_.append(pLabel);
        screen_data_.push_back(QString::number(i + 1));
    }
    return;
}

void Screen::LoadScreen(Text text) {

    return;
}
void Screen::DisplayScreen() {
    cursor_display_count = (cursor_display_count + 1) % (DISPLAY_COUNT << 1);
    for (auto iter = screen_display_.begin(); iter != screen_display_.end(); ++iter) {
        if (cursor_display_count < DISPLAY_COUNT && iter - screen_display_.begin() == relative_position_.raw) {
            QString temp_str = screen_data_[iter - screen_display_.begin()];
            temp_str.insert(relative_position_.column + 1, "</span>");
            temp_str.insert(relative_position_.column, "<span style=\"background-color:#000000\">");
            (**iter).setText(temp_str);
        }
        else {
            (**iter).setText(screen_data_[iter - screen_display_.begin()]);
        }
        //(**iter).setText(QString::number(cursor_display_count + 1));
        (**iter).show();
    }
    return;
}

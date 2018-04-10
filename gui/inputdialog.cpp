#include "inputdialog.h"

QString input_dialog::text(){
    return Input.text();
}

input_dialog::input_dialog(QWidget *parent)
{
    Input.setParent(parent);
    Input.setWindowTitle("请输入...");
    Input.setEchoMode(QLineEdit::Normal);
    Input.setPlaceholderText("*.txt");
    Input.show();
}

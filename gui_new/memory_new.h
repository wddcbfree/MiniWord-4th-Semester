#pragma once
#ifndef STL_IMPLEMENT_TEXT_CLASS_
#define STL_IMPLEMENT_TEXT_CLASS_

#include <cstring>
#include <vector>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <QDebug>
#include <QString>
#include <QChar>
#include "const_define.h"

/*struct ScreenInfo {
    int cursor_x = 0;   //cursor position
    int cursor_y = 0;
    int screen_x = 0;   //screen left-up position
    int screen_y = 0;
};*/

typedef struct Row* Link;
typedef struct block* link;
struct block{ 
	link pre,next;
    QChar s[100];
	int num;
};
struct Row{
	Link pre,next;
	int Row_Num;
	link content;
};

class Text {
public:
    Text(){
        row = 0;
        col = 0;
        row_ = (Link )malloc(sizeof(Row));
        row_->Row_Num = 0;
        row_->pre = NULL;
        row_->next = NULL;
        row_->content = NULL;
    }
    void AddStringEnd(const QString &data, bool is_first);
    void InsertString(const QString &insert_string);
    void Backspace();
    void Delete();
    void DeleteEntireLine();
    void MoveUp();
    void MoveDown();
    void MoveRight();
    void MoveLeft();
    int GetCursorRow();
    int GetCursorCol();
    QChar GetithElement(int i);
    link Locate(int i);
    int CntElement();
    //bool SearchWord(const std::string &search_word);
    //void ReplaceString(const std::string &search_word, const std::string &replace);
    void ConfirmReplace(bool confirm_replace);
    void RefreshScreenPosition();
    int GetNumOfLines();
    QString GetIthString(int i);
    //ScreenInfo GetPosition();
    void RefreshScreenCache();
    QString GetIthCacheString(int i);
    QString BlockCopy(int row1,int col1,int row2,int col2);
    void BlockDelete(int row1,int col1,int row2,int col2);
    void Clear();
private:
	Link row_;
	Link cache_;
    int col;
    int row;
    //ScreenInfo screen_info_;
    std::string replace_;
    int replaced_length;
};

#endif 

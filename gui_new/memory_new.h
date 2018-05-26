#pragma once
#ifndef STL_IMPLEMENT_TEXT_CLASS_
#define STL_IMPLEMENT_TEXT_CLASS_

#define ROW_NUMBER 40
#define COLUME_NUMBER 150

#include <cstring>
#include <vector>
#include <iostream>
#include <cstdio>
#include <cstdlib>

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
	char s[100];
	int num;
};
struct Row{
	Link pre,next;
	int Row_Num;
	link content;
};

class Text {
public:
    void AddStringEnd(const std::string &data);
    void InsertString(const std::string &insert_string);
    void DeleteForward();
    void DeleteBackward();
    void DeleteEntireLine();
    void MoveUp();
    void MoveDown();
    void MoveRight();
    void MoveLeft();
    int GetCursorRow();
    int GetCursorCol();
    char GetithElement(int i);
    link Locate(int i);
    int CntElement();
    int GetEndRowNum();
    bool SearchWord(const std::string &search_word);
    void ReplaceString(const std::string &search_word, const std::string &replace);
    void ConfirmReplace(bool confirm_replace);
    void RefreshScreenPosition();
    int GetNumOfLines();
    std::string GetIthString(int i);
    //ScreenInfo GetPosition();
    void RefreshScreenCache();
    std::string GetIthCacheString(int i);
    std::string BlockCopy(int row1,int col1,int row2,int col2);
    void BlockDelete(int row1,int col1,int row2,int col2);
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

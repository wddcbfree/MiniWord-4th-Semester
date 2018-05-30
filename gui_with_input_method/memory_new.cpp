#include "memory_new.h"

int Text::GetCursorRow() {
    return row;
}

int Text::GetCursorCol() {
    return col;
}

QChar Text::GetithElement(int i) {
    link dest = row_->content;
    for (int j = 1; j <= i; j++) {
        dest = dest->next;
    }
    return dest->s[0];
}

link Text::Locate(int i) {
    link dest = row_->content;
    for (int j = 1; j <= i; j++) {
        dest = dest->next;
    }
    return dest;
}
link Text::f_Locate(int i) {
    Link record = row_;
    int cnt = record->Row_Num;
    if (record->Row_Num > row_f)
        for (int j = 1; j <= cnt - row_f; j++)
            record = record->pre;
    else
        for (int j = 1; j <= row_f - cnt; j++)
            record = record->next;
    link dest = record->content;
    for (int j = 1; j <= i; j++) {
        dest = dest->next;
    }
    return dest;
}

int Text::CntElement() {
    int size = 0;
    link end = row_->content;
    while (end) {
        size++;
        end = end->next;
    }
    return size;
}

void Text::AddStringEnd(const QString &data, bool is_first) {
    Link temp, end = row_;
    while (end->next)
        end = end->next;
    if (!is_first) {
        end->next = (Link)malloc(sizeof(Row));
        temp = end;
        end = end->next;
        end->pre = temp;
        end->Row_Num = end->pre->Row_Num + 1;
        end->next = NULL;
    }
    if (!data.length()) {
        end->content = NULL;
        return;
    }
    end->content = (link)malloc(sizeof(block));
    end->content->pre = NULL;
    end->content->next = NULL;
    end->content->num = 0;
    end->content->s[0] = data[0];
    end->content->s[1] = '\0';
    link media = end->content;
    for (int i = 1; i < data.length(); i++) {
        link medium = (link)malloc(sizeof(block));
        media->next = medium;
        medium->pre = media;
        medium->next = NULL;
        medium->num = media->num + 1;
        medium->s[0] = data[i];
        medium->s[1] = '\0';
        media = medium;
    }
}

void Text::InsertString(const QString &insert_string) {
    if (insert_string.length() == 0) {
        Link temp = (Link)malloc(sizeof(Row));
        temp->pre = row_;
        temp->next = row_->next;
        row_->next = temp;
        if (temp->next)
            temp->next->pre = temp;
        temp->Row_Num = row_->Row_Num + 1;
        link ptr = Locate(col);
        if (ptr) {
            if (ptr->pre)
                ptr->pre->next = NULL;
            ptr->pre = NULL;
            temp->content = ptr;
            link end = ptr;
            while (end) {
                end->num -= col;
                end = end->next;
            }
            temp = temp->next;
            while (temp) {
                temp->Row_Num++;
                temp = temp->next;
            }
            if (col == 0)
                row_->content = NULL;
        }
        else {
            temp->content = NULL;
        }
        row++;
        col = 0;
        row_ = row_->next;
    }
    else {
        int size;
        link end;
        if (!row_->content) {
            size = 0;
            end = NULL;
        }
        else {
            size = 1;
            end = row_->content;
            while (end->next) {
                size++;
                end = end->next;
            }
        }
        if (insert_string.length() <= size - col) {
            link media = end;
            for (int j = 0; j < insert_string.length(); j++) {
                link medium = (link)malloc(sizeof(block));
                media->next = medium;
                medium->pre = media;
                medium->next = NULL;
                medium->s[0] = GetithElement(size - insert_string.length() + j);
                medium->s[1] = '\0';
                media = medium;
            }
            QString s;
            for (int j = col + insert_string.length(); j < size; j++)
                s += GetithElement(j - insert_string.length());
            for (int j = col + insert_string.length(); j < size; j++) {
                link ptr = Locate(j);
                ptr->s[0] = s[j - col - insert_string.length()];
            }
            for (int j = 0; j < insert_string.length(); j++) {
                link ptr = Locate(j + col);
                ptr->s[0] = insert_string[j];
            }
        }
        else {
            link media = end;
            link medium = (link)malloc(sizeof(block));
            if (media) {
                for (int j = size - col; j < insert_string.length(); j++) {
                    link medium = (link)malloc(sizeof(block));
                    media->next = medium;
                    medium->pre = media;
                    medium->next = NULL;
                    medium->num = media->num + 1;
                    medium->s[0] = insert_string[j];
                    medium->s[1] = '\0';
                    media = medium;
                }
                QString s;
                for (int j = col; j < size; j++)
                    s += GetithElement(j);
                for (int j = col; j < size; j++) {
                    link medium = (link)malloc(sizeof(block));
                    media->next = medium;
                    medium->pre = media;
                    medium->next = NULL;
                    medium->num = media->num + 1;
                    medium->s[0] = s[j - col];
                    medium->s[1] = '\0';
                    media = medium;
                }
                for (int j = col; j < size; j++) {
                    link ptr = Locate(j);
                    ptr->s[0] = insert_string[j - col];
                }
            }
            else {
                row_->content = medium;
                medium->num = 0;
                medium->pre = NULL;
                medium->next = NULL;
                medium->s[0] = insert_string[0];
                medium->s[1] = '\0';
                media = medium;
                for (int j = 1; j < insert_string.length(); j++) {
                    medium = (link)malloc(sizeof(block));
                    media->next = medium;
                    medium->num = media->num + 1;
                    medium->pre = media;
                    medium->next = NULL;
                    medium->s[0] = insert_string[j];
                    medium->s[1] = '\0';
                    media = medium;
                }
            }
        }
    }
    for(int j = 0; j < insert_string.length(); j++)
          MoveRight();
    qDebug() << "InsertedString:" << insert_string;
}

void Text::Backspace() {
    if (col != 0) {
        link ptr1 = Locate(col);
        link ptr2 = Locate(col - 1);
        if (ptr1)
            ptr1->pre = ptr2->pre;
        if (ptr2->pre)
            ptr2->pre->next = ptr1;
        else
            row_->content = ptr1;
        col--;
    }
    else {
        if (row != 0) {
            Link temp = row_->pre;
            temp->next = row_->next;
            if (row_->next)
                row_->next->pre = temp;
            link end = temp->content;
            if (!end) {
                int size = 0;
                temp->content = row_->content;
                col = 0;
                row--;
                row_ = temp;
            }
            else {
                int size = 1;
                while (end->next) {
                    size++;
                    end = end->next;
                }
                end->next = row_->content;
                if (row_->content)
                    row_->content->pre = end;
                link media = row_->content;
                while (media) {
                    media->num += size;
                    media = media->next;
                }
                col = size;
                row--;
                row_ = temp;
            }
        }
    }
}

void Text::Delete() {
    link ptr = Locate(col);
    if (ptr) {
        col++;
        Backspace();
    }
    else {
        if (row_->next) {
            row++;
            row_ = row_->next;
            col = 0;
            Backspace();
        }
    }
}

void Text::DeleteEntireLine() {
    if (row_->next && row_->pre) {
        row_->pre = row_->next;
        row_->next->pre = row_->pre;
        row_ = row_->next;
        row++;
        int size = 0;
        link end = row_->content;
        while (end) {
            end = end->next;
            size++;
        }
        if (col > size)
            col = size;
        Link temp = row_;
        while (temp) {
            temp->Row_Num--;
            temp = temp->next;
        }
        return;
    }
    if (!row_->next && !row_->pre) {
        col = 0;
        row_->content = NULL;
        return;
    }
    if (!row_->next && row_->pre) {
        row_->pre->next = NULL;
        row_ = row_->pre;
        row--;
        int size = 0;
        link end = row_->content;
        while (end) {
            end = end->next;
            size++;
        }
        if (col > size)
            col = size;
        return;
    }
    if (row_->next && !row_->pre) {
        row_ = row_->next;
        row_->pre = NULL;
        MoveDown();
        Link temp = row_;
        while (temp) {
            temp->Row_Num--;
            temp = temp->next;
        }
        return;
    }
}

void Text::MoveUp() {
    if (row != 0) {
        row_ = row_->pre;
        row--;
        int size = 0;
        if (row_) {
            link end = row_->content;
            while (end) {
                end = end->next;
                size++;
            }
        }
        if (col > size)
            col = size;
    }
}

void Text::MoveDown() {
    if (row_->next) {
        row_ = row_->next;
        row++;
        int size = 0;
        link end = row_->content;
        while (end) {
            end = end->next;
            size++;
        }
        if (col > size)
            col = size;
    }
}

void Text::MoveRight() {
    int size = 0;
    link end = row_->content;
    while (end) {
        end = end->next;
        size++;
    }
    if (col < size)
        col++;
    else {
        if (row_->next) {
            col = 0;
            row++;
            row_ = row_->next;
        }
    }
}

void Text::f_MoveRight() {
    Link record = row_;
    int cnt = record->Row_Num;
    if (record->Row_Num > row_f)
        for (int j = 1; j <= cnt - row_f; j++)
            record = record->pre;
    else
        for (int j = 1; j <= row_f - cnt; j++)
            record = record->next;
    int size = 0;
    link end = record->content;
    while (end) {
        end = end->next;
        size++;
    }
    if (col_f < size)
        col_f++;
    else {
        if (record->next) {
            col_f = 0;
            row_f++;
        }
    }
}

void Text::MoveLeft() {
    if (col != 0)
        col--;
    else {
        if (row_->pre) {
            row--;
            row_ = row_->pre;
            int size = 0;
            link end = row_->content;
            while (end) {
                end = end->next;
                size++;
            }
            col = size;
        }
    }
}

int Text::GetNumOfLines() {
    int cnt = row;
    Link end = row_;
    while (end->next) {
        end = end->next;
        cnt++;
    }
    return cnt + 1;
}

QString Text::GetIthString(int i) {
    QString str = "";
    Link temp = row_;
    if (row > i) {
        int cnt = row;
        while (cnt != i) {
            temp = temp->pre;
            cnt--;
        }
    }
    if (row < i) {
        int cnt = row;
        while (cnt != i) {
            temp = temp->next;
            cnt++;
        }
    }
    int size = 0;
    link end = temp->content;
    while (end) {
        str = str + end->s[0];
        end = end->next;
    }
    return str;
}
/*
bool Text::SearchWord(const std::string &search_word){
        link temp = Locate(col);
        int cnt = col;
        while(temp){
                link ptr = temp;
                bool flag = 1;
                for(int j=0;j<search_word.length() & flag;j++){
                        if(!ptr || ptr->s[0] != search_word[j])
                            flag = 0;
                        ptr = ptr->next;
                }
                if(flag){
                        break;
                        col = cnt;
                        return 1;
                }
                temp = temp->next;
                cnt++;
        }
        return 0;
}
void Text::ReplaceString(const std::string &search_word, const std::string
&replace){ bool signal = SearchWord(search_word); replace_ = replace;
        replaced_length = search_word.length();
        //if(!signal)
}
*/

bool Text::SearchWord(const QString &search_word) {
    qDebug()<<search_word[0];
    col_f = col;
    row_f = row;
    link temp = f_Locate(col_f);
    while (!temp) {
        f_MoveRight();
        temp = f_Locate(col_f);
        if (row_f == GetNumOfLines() - 1 && !temp)
            return 0;
    }
    qDebug()<<temp->s[0];
    bool flag = 1;
    while (temp) {
        qDebug()<<temp->s[0];
        int record1 = col_f;
        int record2 = row_f;
        link ptr = temp;
        flag = 1;
        for (int j = 0; j < search_word.length() & flag; j++) {
            qDebug()<<"loop"<<ptr->s[0];
            if (ptr->s[0] != search_word[j])
                flag = 0;
            f_MoveRight();
            ptr = f_Locate(col_f);
            while (!ptr) {
                f_MoveRight();
                ptr = f_Locate(col_f);
                if (row_f == GetNumOfLines() - 1 && !ptr)
                    return 0;
            }
        }
        if (flag) {
            qDebug()<<record1<<record2;
            col = record1;
            row = record2;
            Link record = row_;
            int i;
            int cnt = row_->Row_Num;
            if (record->Row_Num > row)
                for (i = 1; i <= cnt - row; i++)
                    record = record->pre;
            else
                for (i = 1; i <= row - cnt; i++)
                    record = record->next;
            row_ = record;
            return 1;
        }
        col_f = record1;
        row_f = record2;
        f_MoveRight();
        temp = f_Locate(col_f);
        while (!temp) {
            f_MoveRight();
            temp = f_Locate(col_f);
            if (row_f == GetNumOfLines() - 1 && !temp)
                return 0;
        }
    }
    return 0;
}

void Text::ConfirmReplace(bool confirm_replace) {
    if (confirm_replace) {
        for (int j = 1; j <= replaced_length; j++)
            Delete();
        // InsertString(replace_);
    }
}

void Text::BlockCopy(int row1, int col1, int row2, int col2) {
    if (row1 > row2) {
        int temp = row2;
        row2 = row1;
        row1 = temp;
        int temp2 = col2;
        col2 = col1;
        col1 = temp2;
    }
    if (row1 == row2 && col1 > col2) {
        int temp = col2;
        col2 = col1;
        col1 = temp;
    }
    Link record = row_;
    int i;
    int cnt = row_->Row_Num;
    if (record->Row_Num > row1)
        for (i = 1; i <= cnt - row1; i++)
            record = record->pre;
    else
        for (i = 1; i <= row1 - cnt; i++)
            record = record->next;
    row1_b = record;
    qDebug() << row1_b->Row_Num;
    link temp = record->content;
    qDebug() << col1;
    for (int i = 0; i < col1; i++) {
        temp = temp->next;
        qDebug() << i;
    }
    temp1_b = temp;
    qDebug() << temp1_b->num;

    record = row_;
    cnt = row_->Row_Num;
    if (record->Row_Num > row2)
        for (i = 1; i <= cnt - row2; i++)
            record = record->pre;
    else
        for (i = 1; i <= row2 - cnt; i++)
            record = record->next;
    row2_b = record;
    temp = record->content;
    for (int i = 0; i < col2; i++)
        temp = temp->next;
    temp2_b = temp;
    //qDebug()<<temp1_b->s[0];
    //qDebug()<<temp2_b->num;
}

void Text::BlockPaste() {
    QString s = "";
    link ptr = temp1_b;
    if (row1_b == row2_b) {
        int value1 = temp1_b->num;
        int value2 = 0;
        if (!temp2_b) {
            link f_ptr = ptr;
            while (f_ptr != temp2_b) {
                f_ptr = f_ptr->next;
                value2++;
            }
        }
        else
            value2 = temp2_b->num - value1;
        for (int i = value2; i > 0; i--) {
            s += ptr->s[0];
            ptr = ptr->next;
        }
        InsertString(s);
    }
    else {
        while (ptr) {
            s += ptr->s[0];
            ptr = ptr->next;
        }
        InsertString(s);
        qDebug() << s;
        // if(s.length())
        // MoveRight();
        int flag = 1;
        if (!s.length())
            flag = 0;
        Link end = row1_b;
        for (int i = 1; i < row2_b->Row_Num - row1_b->Row_Num; i++) {
            s = "";
            if (flag)
                InsertString("");
            end = end->next;
            ptr = end->content;
            while (ptr) {
                s += ptr->s[0];
                ptr = ptr->next;
            }
            InsertString(s);
            if (!s.length())
                flag = 0;
            else
                flag = 1;
        }
        end = row2_b;
        s = "";
        if (flag)
            InsertString(s);
        ptr = end->content;
        int value = 0;
        if (!temp2_b) {
            link f_ptr = ptr;
            while (f_ptr != temp2_b) {
                f_ptr = f_ptr->next;
                value++;
            }
        }
        else
            value = temp2_b->num;
        for (int i = value; i > 0; i--) {
            s += ptr->s[0];
            ptr = ptr->next;
        }
        InsertString(s);
    }
}

void Text::BlockDelete(int row1, int col1, int row2, int col2) {
    if (row1 > row2) {
        int temp = row2;
        row2 = row1;
        row1 = temp;
        int temp2 = col2;
        col2 = col1;
        col1 = temp2;
    }
    if (row1 == row2 && col1 > col2) {
        int temp = col2;
        col2 = col1;
        col1 = temp;
    }
    qDebug() << "Block Deleting: " << row1 << "," << col1 << "  " << row2 << ","
        << col2;
    if (row1 == row2) {
        link temp1 = Locate(col1);
        link temp2 = Locate(col2);
        if (temp1->pre)
            temp1->pre->next = temp2;
        else
            row_->content = temp2;
        if (temp2) {
            temp2->pre = temp1->pre;
            link ptr = temp2;
            while (ptr) {
                ptr->num -= (col2 - col1);
                ptr = ptr->next;
            }
        }
        col = col1;
    }
    else {
        Link record = row_;
        if (record->Row_Num == row1) {
            for (int i = 1; i <= row2 - row1; i++)
                record = record->next;
        }
        else {
            for (int i = 1; i <= row2 - row1; i++)
                row_ = row_->pre;
        }
        link temp1 = Locate(col1);
        link temp2 = record->content;
        for (int i = 0; i < col2; i++)
            temp2 = temp2->next;

        if (!col1) {
            row_->content = temp2;
            if (temp2)
                temp2->pre = NULL;
        }
        else {
            temp1 = Locate(col1 - 1);
            temp1->next = temp2;
            if (temp2)
                temp2->pre = temp1;
        }

        row_->next = record->next;
        if (record->next)
            record->next->pre = row_;
        if (temp2) {
            link ptr = temp2;
            while (ptr) {
                ptr->num -= col2 - col1;
                ptr = ptr->next;
            }
        }
        row = row1;
        col = col1;
    }
}

void Text::Clear() {
    row = 0;
    col = 0;
    while (row_->pre)
        row_ = row_->pre;
    while (row_) {
        Link end = row_->next;
        free(row_);
        row_ = end;
    }
    row_ = (Link)malloc(sizeof(Row));
    row_->Row_Num = 0;
    row_->pre = NULL;
    row_->next = NULL;
    row_->content = NULL;
}

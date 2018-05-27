#include"memory_new.h"

int Text::GetCursorRow(){
	return row;
}

int Text::GetCursorCol(){
	return col;
}


char Text::GetithElement(int i){
	link dest = row_->content;
	for(int j=1;j<=i;j++){
		dest = dest->next;
	}
	return dest->s[0];
}

link Text::Locate(int i){
	link dest = row_->content;
	for(int j=1;j<=i;j++){
		dest = dest->next;
	}
	return dest;
}

int Text::CntElement(){
	int size = 0;
	link end = row_->content;
	while(end){
		size++;
		end = end->next;
	}
}
  
void Text::AddStringEnd(const std::string &data){
	Link temp, end = row_;
	while(end->next)
	    end = end->next;
	if(end->content){
	    end->next = (Link )malloc(sizeof(Row));
	    temp = end;
	    end = end->next;
        end->pre = temp;
	    end->Row_Num = end->pre->Row_Num + 1;
	    end->next = NULL;
	}
	const char* cont = data.c_str();
	end->content = (link )malloc(sizeof(block));
	end->content->pre = NULL;
	end->content->next = NULL;
	end->content->num = 0;
	end->content->s[0] = cont[0];
	end->content->s[1] = '\0';
	link media = end->content;
	for(int i=1;i<data.length();i++){
		link medium = (link )malloc(sizeof(block));
		media->next = medium;
		medium->pre = media;
		medium->next = NULL;
		medium->num = media->num+1;
		medium->s[0] = cont[i];
	    medium->s[1] = '\0';
		media = medium; 
	}     
}  

void Text::InsertString(const std::string &insert_string){
	if(insert_string.length() == 0){
		Link temp = (Link )malloc(sizeof(Row));
		temp->pre = row_;
		temp->next = row_->next;
		row_->next = temp;
		temp->Row_Num = row_->Row_Num + 1;
		link ptr = Locate(col);
		if(ptr){
		if(ptr->pre)
		    ptr->pre->next = NULL;
		ptr->pre = NULL;
		temp->content = ptr;
		link end = ptr;
		while(end){
			end->num -= col;
			end = end->next;
		}
		temp = temp->next;
		while(temp){
			temp->Row_Num++;
			temp = temp->next;
		}
		if(col == 0)
			row_->content = NULL;
		}
		else
			temp->content = NULL;
		row++;
		col = 0;
		row_ = row_->next;	
	}
	else{
	    const char* str = insert_string.c_str();
	    int size;
	    link end;
	    if(!row_->content){
	        size=0;
	        end = NULL;
	    }
	    else{
	        size = 1;
	        end = row_->content;
	        while(end->next){
		        size++;
		        end = end->next;
	        }
            }
	    if(insert_string.length() <= size-col){
		    link media = end;
	        for(int j = 0;j < insert_string.length();j++){
		        link medium = (link )malloc(sizeof(block));
		        media->next = medium;
		        medium->pre = media;
		        medium->next = NULL;
		        medium->s[0] = GetithElement(size-insert_string.length()+j);
	                medium->s[1] = '\0';
			media = medium; 
	        }
	        std::string s;
	        for(int j = col + insert_string.length(); j < size;j++)
	            s += GetithElement(j-insert_string.length());
	        for(int j = col + insert_string.length(); j < size;j++){
	    	    link ptr = Locate(j);
	    	    ptr->s[0] = s[j-col-insert_string.length()];
		    }
	        for(int j = 0;j < insert_string.length();j++){
	            link ptr = Locate(j+col);
	    	    ptr->s[0] = str[j];
	        }
        }
        else{
    	    link media = end;
    	    link medium = (link )malloc(sizeof(block));
    	    if(media){
			    for(int j = size-col ;j < insert_string.length();j++){
		            link medium = (link )malloc(sizeof(block));
		            media->next = medium;
		            medium->pre = media;
		            medium->next = NULL;
		            medium->num = media->num+1;
		            medium->s[0] = str[j];
	                medium->s[1] = '\0';
			        media = medium;
	            }
	            std::string s;
	            for(int j = col;j < size;j++)
	                s += GetithElement(j);
	            for(int j = col;j < size;j++){
		            link medium = (link )malloc(sizeof(block));
		            media->next = medium;
		            medium->pre = media;
		            medium->next = NULL;
		            medium->num = media->num+1;
		            medium->s[0] = s[j-col];
	                medium->s[1] = '\0';
			        media = medium; 
	            }
	            for(int j = col;j < size;j++){
		            link ptr = Locate(j);
	    	        ptr->s[0] = str[j-col];
	            }
		    }
		    else{
		        row_->content = medium;
		        medium->num = 0;
		        medium->pre = NULL;
		        medium->next = NULL;
		        medium->s[0] = insert_string[0];
		        medium->s[1] = '\0';
		        media = medium;
		        for(int j=1;j<insert_string.length();j++){
		    	    medium = (link )malloc(sizeof(block));
		    	    media->next = medium;
		            medium->num = media->num+1;
		            medium->pre = media;
		            medium->next = NULL;
		            medium->s[0] = insert_string[j];
	                medium->s[1] = '\0';
			        media = medium;
			    }
		    }
	    }
    }
}

void Text::Backspace(){
	if(col != 0){
		link ptr1 = Locate(col);
		link ptr2 = Locate(col-1);
		if(ptr1)
		    ptr1->pre = ptr2->pre;
		if(ptr2->pre)
		    ptr2->pre->next = ptr1;
		else
		    row_->content = ptr1;
		col--;		
	}
	else{
	    if(row != 0){
		    Link temp = row_->pre;
		    temp->next = row_->next;
		    if(row_->next)
		        row_->next->pre = temp;
		    link end = temp->content;
		    if(!end){
	            int size=0;
	            temp->content = row_->content;
	            col = 0;
		        row--; 
		        row_ = temp;
	        }
	        else{
	            int size = 1;
	            while(end->next){
		            size++;
		            end = end->next;
	            }
	            end->next = row_->content;
		        if(row_->content)
		            row_->content->pre = end;
		        link media = row_->content;
		        while(media){
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

void Text::Delete(){
	link ptr = Locate(col);
	if(ptr){
		col++;
		Backspace();
	}
	else{
		if(row_->next){
			row++;
			row_ =row_->next;
			col = 0;
			Backspace();
		}
	}
}

void Text::DeleteEntireLine(){
	if(row_->next && row_->pre){
		row_->pre = row_->next;
		row_->next->pre = row_->pre; 
		row_ = row_->next;
		row++;
		int size=0;
		link end = row_->content;
		while(end){
		    end = end->next;
		    size++;
		}
		if(col > size)
		    col = size;
		Link  temp = row_;
		while(temp){
			temp->Row_Num--;
			temp = temp->next;
		}
		return;
	}
	if(!row_->next && !row_->pre){
		col = 0;
		row_->content = NULL;
		return;
	}
	if(!row_->next && row_->pre){
		row_->pre->next = NULL;
		row_ = row_->pre;
        row--;
        int size=0;
		link end = row_->content;
		while(end){
		    end = end->next;
		    size++;
		}
		if(col > size)
		    col = size;
		return;
	}
	if(row_->next && !row_->pre){
		row_ = row_->next;
		row_->pre = NULL;
		MoveDown();
		Link temp = row_;
		while(temp){
			temp->Row_Num--;
			temp = temp->next;
		}
		return;
	}	
}

void Text::MoveUp(){
	if(row != 0){
	    row_ = row_->pre;
	    row--;
	    int size=0;
		link end = row_->content;
		while(end){
		    end = end->next;
		    size++;
		}
	    if(col > size)
	        col = size;
	} 
}

void Text::MoveDown(){
	if(row_->next){
	    row_ = row_->next;
		row++;
		int size=0;
		link end = row_->content;
		while(end){
		    end = end->next;
		    size++;
		}
	    if(col > size)
	        col = size;
	}
}

void Text::MoveRight(){
	int size=0;
	link end = row_->content;
	while(end){
		end = end->next;
		size++;
	}
    if(col < size)
	    col++;
	else{
		if(row_->next){
			col = 0;
			row++;
			row_ = row_->next;
		}		
	}    
}

void Text::MoveLeft(){
	if(col != 0)
		col--;
	else{
		if(row_->pre){
			row--;
			row_ = row_->pre;
			int size=0;
	        link end = row_->content;
	        while(end){
		        end = end->next;
		        size++;
	        }
	        col = size;
		}
	}	
}

int Text::GetNumOfLines(){
    int cnt = row;
    Link end = row_;
	while(end->next){
	    end = end->next;
	    cnt++;
	}
	return cnt;
} 

std::string Text::GetIthString(int i){
	std::string str;
	Link temp = row_;
	if(row > i){
		int cnt = row;
		while(cnt != i){
			temp = temp->pre;
			cnt--;
		}
	}
	if(row < i){
		int cnt = row;
		while(cnt != i){
			temp = temp->next;
			cnt++;
		}
	}
	int size=0;
	link end = temp->content;
	while(end){
		str += end->s[0]; 
	    end = end->next;
	}
	return str;
}

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

void Text::ReplaceString(const std::string &search_word, const std::string &replace){
	bool signal = SearchWord(search_word);
	replace_ = replace;
	replaced_length = search_word.length();
	//if(!signal)	   
} 

void Text::ConfirmReplace(bool confirm_replace){
	if(confirm_replace){
	    for(int j=1;j<=replaced_length;j++)
	        Delete();
	    InsertString(replace_);
	}	
}

std::string Text::BlockCopy(int row1,int col1,int row2,int col2){
	if(row1 > row2){
		int temp = row2;
		row2 = row1;
		row1 = temp;
	}
	if(row1==row2 && col1 > col2){
		int temp = col2;
		col2 = col1;
		col1 = temp;
	}
	std::string str;
	Link record = row_;
	for(int i=1;i<=row2-row1+1;i++){
		if(i==1){
			if(row1==row2){
				link temp = Locate(col1);
			    while(temp!=Locate(col2)){
				    str += temp->s[0];
				    temp = temp->next;
			    }
			}
			else{
			    link temp = Locate(col1);
			    while(temp){
				    str += temp->s[0];
				    temp = temp->next;
			    }
			}
		}
		else if(i==row2-row1+1){
			link media = record->content;
			for(int i=0;i<col2;i++){
				str += media->s[0];
				media = media->next;
			}
		}
		else{
			link media = record->content;
			while(media){
			    str += media->s[0];
				media = media->next;
			}
		}
		record = record->next;
	}
	return str;
}

void Text::BlockDelete(int row1,int col1,int row2,int col2){
	if(row1 > row2){
		int temp = row2;
		row2 = row1;
		row1 = temp;
	}
	if(row1==row2 && col1 > col2){
		int temp = col2;
		col2 = col1;
		col1 = temp;
	}
	if(row1 == row2){
		link temp1 = Locate(col1);
		link temp2 = Locate(col2);
		if(temp1->pre)
		    temp1->pre->next = temp2;
		if(temp2){
		    temp2->pre = temp1->pre;
		    link ptr = temp2;
		    while(ptr){
		    	ptr->num -= col2-col1;
		    	ptr = ptr->next;
			}
		}
	}
	else{
		Link record = row_;
	    for(int i=1;i<=row2-row1;i++)
            record = record->next;
        link temp1 = Locate(col1);    
		link temp2 = record->content;	 
	    for(int i=0;i<col2;i++)
	    	temp2 = temp2->next;
	    if(temp1->pre)
		    temp1->pre->next = temp2;
		if(temp2){
		    temp2->pre = temp1->pre;
		    link ptr = temp2;
		    while(ptr){
		    	ptr->num -= col2-col1;
		    	ptr = ptr->next;
			}
		}
	}
}

void Text::Clear(){
    row = 0;
    col = 0;	
    row_ = (Link )malloc(sizeof(Row));
		row_->Row_Num = 0;
		row_->pre = NULL;
		row_->next = NULL;
		row_->content = NULL;
}

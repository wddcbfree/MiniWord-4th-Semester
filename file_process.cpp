//
//  file_process.cpp
//  MiniWord
//
//  Created by 温和 on 2018/3/9.
//  Copyright © 2018年 温和. All rights reserved.
//
#include <fstream>
using namespace std;

class FileProcess{
    private:
        ofstream file_self;
        void init(const char order, const string address);//打开文件流
    public:
        string read(const int line_num);
};

void FileProcess::init(const char order, const string address){
    if(order == 'C'){//创建
        FileProcess::file_self.open(address,ios::out|ios::in);
    }
    else if(order == 'O'){//打开 还需添加判断文件是否存在
        FileProcess::file_self.open(address,ios::in|ios::out);
    }
}

string FileProcess::read(const int line_num){//将文件的内容读取到内存
    string data;
    //FileProcess::file_self.seekg(0,ios::beg);
    //return FileProcess::file_self.getline(data,'\n');
}

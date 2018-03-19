#ifndef file_process_h
#define file_process_h

#include <iostream>
#include <fstream>
#include <string>

class FileProcess{
public:
    std::string read();//用于读取文件，每使用一次，读取一行
    FileProcess(const std::string address);//打开文件流
    bool is_end();//读取文件内容时，用于判断是否为结尾
private:
    std::fstream file_self;
};

#endif /* file_process_h */

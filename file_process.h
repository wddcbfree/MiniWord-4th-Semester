#ifndef file_process_h
#define file_process_h

#include <iostream>
#include <fstream>
#include <istream>
#include <string>

class FileProcess{
public:
    std::string read();//用于读取文件，每使用一次，读取一行
    std::fstream file_self;
    FileProcess(const std::string address);//打开文件流
};

#endif /* file_process_h */

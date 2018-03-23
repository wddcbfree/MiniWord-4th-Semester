#ifndef file_process_h
#define file_process_h

#include <iostream>
#include <fstream>
#include <string>

class FileProcess{
public:
    std::string read();//用于读取文件，每使用一次，读取一行（空行照样读取）
    bool open(const std::string address);//打开文件
    bool create(const std::string address);//创建文件
    bool is_end();//读取文件内容时，用于判断是否为文件结尾
    bool pre_write();//写入前使用
    void write(const std::string text);//用于将字符串写入文件
    void close();//关闭文件
private:
    std::fstream file_self;
    std::string address;
};

#endif /* file_process_h */

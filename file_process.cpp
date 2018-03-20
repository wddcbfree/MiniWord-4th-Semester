#include "file_process.h"

FileProcess::FileProcess(const std::string file_address){
    address = file_address;
    file_self.open(address,std::ios::in);
}

std::string FileProcess::read(){
    if(is_end() == 0){
        std::string data;
        getline(file_self,data);
        return data+"\n";
    }
    else{
        return "";
    }
}

bool FileProcess::is_end(){
    if(file_self.tellg() == -1)
        return 1;
    else
        return 0;
}

void FileProcess::pre_save(){
    file_self.close();
    file_self.open(address,std::ios::trunc | std::ios::out);
    file_self.seekg(std::ios::beg);
    return;
}

void FileProcess::write(const std::string text){
    file_self << text;
    return;
}

void FileProcess::close(){
    file_self.close();
    return;
}

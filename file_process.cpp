#include "file_process.h"
bool FileProcess::create(const std::string file_address){
    address = file_address;
    file_self.open(address,std::ios::trunc | std::ios::out);
    if(file_self.is_open()){
        file_self.close();
        return true;
    }
    file_self.close();
    return false;
}

bool FileProcess::open(const std::string file_address){
    address = file_address;
    file_self.open(address,std::ios::in);
    if(file_self.is_open()){
        return true;
    }
    return false;
}

std::string FileProcess::read(){
    if(is_end() == 0){
        std::string data;
        getline(file_self,data);
        return data+"\n";
    }
    else{
        file_self.close();
        return "";
    }
}

bool FileProcess::is_end(){
    if(file_self.tellg() == -1)
        return true;
    else
        return false;
}

bool FileProcess::pre_write(){
    file_self.open(address,std::ios::trunc | std::ios::out);
    if(file_self.is_open()){
        file_self.seekg(std::ios::beg);
        return true;
    }
    return false;
    
}

void FileProcess::write(const std::string text){
    file_self << text;
    return;
}

void FileProcess::close(){
    file_self.close();
    return;
}

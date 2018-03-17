#include "file_process.h"

FileProcess::FileProcess(const std::string address){
    file_self.open(address,std::ios::in);
}

std::string FileProcess::read(){
    if(FileProcess::file_self.is_open()){
        std::string data;
        getline(file_self,data);
        return data;
    }
    else{
        return "error: file not opened.\n";
    }
}

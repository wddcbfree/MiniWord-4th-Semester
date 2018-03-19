#include "file_process.h"

FileProcess::FileProcess(const std::string address){
    file_self.open(address,std::ios::in);
}

std::string FileProcess::read(){
    if(FileProcess::file_self.is_open()){
        std::string data;
        getline(file_self,data);
        std::cout<<"length = "<<file_self.tellg()<<std::endl;
        return data;
    }
    else{
        exit(0);
    }
}

bool FileProcess::is_end(){
    if(file_self.tellg() == -1)
        return 1;
    else
        return 0;
}

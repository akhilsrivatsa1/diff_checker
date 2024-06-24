#include <iostream>
#include "../include/file_util.h"
#include <vector>

int main(int argc, char* argv[]){

    if(argc != 3){
        std::cerr << "Incorrect Parameters, please provide two file directories to compare" << std::endl;
        return 1;
    }
    std::string directoryPathOne = argv[1];
    std::string directoryPathTwo = argv[2];

    if(!util::isPathValid(directoryPathOne)){
        std::cerr << "Invalid Path: " << directoryPathOne << std::endl;
        return 1;
    }

    if(!util::isPathValid(directoryPathTwo)){
        std::cerr << "Invalid Path: " << directoryPathTwo << std::endl;
        return 1;
    }
    util::compareDirectories(directoryPathOne,directoryPathTwo);
    
    return 0;


}
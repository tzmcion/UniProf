#include "../Helpers.h"

std::vector<std::string> get_array_from_file(const char* path){
    std::vector <std::string> lines; 
    std::string line;
    std::fstream data_file(path);
    while(getline(data_file,line)){
        lines.push_back(line);
    }
    data_file.close();
    return lines;
}
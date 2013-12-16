#include <fstream>
#include <iostream>
#include <string>



int main() {
    const char *filename = "euler/src/problem11";
    std::fstream in(filename);
    if(!in.good()) {
        std::cout << "No such file: " << filename <<std::endl;
        return 1;
    }
        
    while(!in.eof()) {
        std::string line;
        std::getline(in, line);
        std::cout << line << "\n";
    }    
    
    return 0;
}
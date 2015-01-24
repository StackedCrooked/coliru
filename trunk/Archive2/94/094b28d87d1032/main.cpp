#include <fstream>
#include <string>
#include <iostream>
#include <exception>
 
int main()
{
    try{
        
        //std::string s;
        std::ifstream file("a.out");
    
        while (!file.eof()){
            std::string s;
            file >> s;
            std::cout << s << std::endl;
        }
    
        // std::cout << s << std::endl;
    }
    catch(std::exception &e){
        std::cout << "err" << e.what() << std::endl;
    }
}
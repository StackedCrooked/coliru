#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdint>
 
int main()
{
    std::string msg = "1 2 3 <p>a b c</p>";
    std::istringstream iss(msg);
   
    int one, two, three;
    iss >> one;
    iss >> two;
    iss >> three;
    
    char c;
    
    iss >> c;
    
    int length = 13;
    std::string str;
    str.resize(length, ' '); // reserve space
    char* begin = &*str.begin();

    iss.read(begin, length);
    
    std::cout <<c<<str <<std::endl;
   
}
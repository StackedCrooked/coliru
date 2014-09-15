#include <sstream>
#include <string>
#include <iostream>

int main()
{
    int filenameIndex = 1;      
    std::stringstream temp_str;
    temp_str<<(filenameIndex);
    std::string str = temp_str.str();
    const char* cstr2 = str.c_str();
    std::cout << cstr2;
}

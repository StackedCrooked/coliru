#include <iostream>
#include <sstream>
#include <map>
#include <string>

std::string foo(const char* lnumber)
{
    std::istringstream sData("A,B,C");
    char delim = ',';                 
    
    std::map<std::string, std::string> tMap;
    std::string newkey;
    
    while(std::getline(sData, newkey, delim))
        tMap[newkey] = "yes";

    return tMap[lnumber];
}

int main() 
{
    std::string value = foo("C");
    std::cout << value;
}
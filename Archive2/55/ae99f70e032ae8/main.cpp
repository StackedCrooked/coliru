#include <iostream>
#include <sstream>
#include <map>
#include <string>

char* foo(char* lnumber)
{
    std::stringstream sData = "A,B,C";
    char delim = ',';                 
    
    std::map<std::string, std::string> tMap;
    std::string newkey;
    
    while(std::getline(sData, newKey))
        tMap[std::move(newKey)] = "yes";

    return strdup(tMap[lnumber].c_str());
}
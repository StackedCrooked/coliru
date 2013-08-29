#include <iostream>
#include <stdio.h>
#include <map>
int main()
{
    std::map<std::string,std::string> m;
    std::cout << (m["x"].find("a") != std::string::npos);
    return 0;
}
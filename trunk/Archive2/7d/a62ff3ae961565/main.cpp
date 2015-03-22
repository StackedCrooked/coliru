#include <iostream>
#include <string>
#include <stdexcept>

std::string getString(const std::string& fullString)
{
    size_t pos = fullString.rfind('|');
    if (pos == std::string::npos)
       throw std::runtime_error("Could not find a '|'!");
    
    return fullString.substr(pos+1);
}

int main()
{
    std::string str("{[(2015/11/30|01:07:53.357|-1227639088|DefaultThread|./src/Myprogram.cpp:564|int main(int, argv**))]} Server Starting....");
    std::cout << getString(str) << std::endl;
    return 0;
}
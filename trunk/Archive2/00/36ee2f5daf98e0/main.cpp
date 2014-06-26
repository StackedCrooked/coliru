#include <iostream>
#include <string>
#include <algorithm>

void addone(std::string &str) {
  std::for_each(str.begin(), str.end(), [](char &c) { ++c; });    
}

int main()
{
    std::string str("ABCDEFG");
    std::cout << "Before: " << str << std::endl;
    addone(str);
    std::cout << "After : " << str << std::endl;
    
    return 0;
}
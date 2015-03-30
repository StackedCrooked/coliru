#include <iostream>
#include <string>
#include <algorithm>

int main () {
    
    const std::string s = "Test string.";
    std::for_each(s.rbegin(), s.rend(), [](const char& c){ std::cout << c; });
    std::cout << std::endl;

}

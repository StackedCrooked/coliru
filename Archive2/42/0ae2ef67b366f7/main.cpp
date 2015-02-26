#include <string>
#include <iostream>

int main() {
    std::string s = "abcdef";
    
    std::string s2 = s;
    
    auto begin = const_cast<std::string const &>(s2).begin();
    auto end = s2.end();
    
    std::cout << end - begin << '\n';
}
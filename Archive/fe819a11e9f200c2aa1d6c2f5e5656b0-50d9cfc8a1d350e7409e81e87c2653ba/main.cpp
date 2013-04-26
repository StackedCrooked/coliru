#include <iostream>
#include <string>

using namespace std;


int main() {
    string s1("test\0test");
    std::cout << s1 << std::endl;
    std::cout << s1.c_str() << std::endl;
    
    string s2("test");
    s2 += '\0';
    s2 += "test";
    std::cout << s2 << std::endl;
    std::cout << s2.c_str() << std::endl;
}
#include <iostream>
#include <string>

int main() {
    std::string s1 = "test 1";
    
    {
        std::string s1 = "test 2";
        std::cout<< s1 << std::endl;
    }
    
    std::cout<< s1 << std::endl;
}
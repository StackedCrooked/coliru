#include <iostream>
#include <string>

int main()
{
    std::string testStr = "TEST string";
    if (testStr.find("TEST") != std::string::npos) {
        std::cout << "Found string\n";
    }
    if (testStr.find("TEST") == 0) {
        std::cout << "Found string, at index 0\n";
    }
}
#include <iostream>
#include <string>

int main(int, char*[]) {
    std::string word("żółć");
    const char* x = word.c_str();
    std::cout << x;
}
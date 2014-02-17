#include <algorithm>
#include <string>
#include <iostream>

int main() {
    std::string str1 = "Apple";
    std::string str2 = "Potato";
    std::swap(str1, str2);
    std::cout << str1 << '\n' << str2;
}
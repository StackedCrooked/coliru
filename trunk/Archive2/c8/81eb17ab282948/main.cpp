#include <string>
#include <iostream>

int main() {
    std::string s1 = "India is my country";
    std::cout << s1.find_first_of(' ', 4) << '\n';
    std::cout << s1.find_first_of(' ', 6) << '\n';
}
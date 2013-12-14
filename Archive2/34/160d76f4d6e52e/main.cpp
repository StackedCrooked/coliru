#include <iostream>

int main() {
    std::string&& s = "hi there";
    std::cout << s << "\n";
    std::string&& s2 = std::string("hi there");
    std::cout << s2 << "\n";
    std::string& s3 = s2;
    std::cout << s3 << "\n";
    std::string& s4 = "hi there";
    std::cout << s4 << "\n";
}
#include <vector>
#include <vector>
#include <iostream>

int main() {
    std::vector<std::string> strings;
    strings.push_back("hello");
    auto &s = strings[0];
    //auto s = strings[0]; // copy
    strings.push_back("beep");
    std::cout << s;
}
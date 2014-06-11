#include "/Archive2/55/7d62aaf566946a/main.cpp"
#include <sstream>
#include <iostream>

int main() {
    std::istringstream ss("Hello");
    std::string str;
    std::getline(ss, str);
    std::cout << str << std::endl;
}
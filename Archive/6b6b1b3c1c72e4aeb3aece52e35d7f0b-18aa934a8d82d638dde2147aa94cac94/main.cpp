#include <iostream>
#include <string>

int main() {
    std::string str = "tracing-1";
    str = str.substr(str.find('-') + 1);
    int num = std::stoi(str);
    std::cout << num;
}
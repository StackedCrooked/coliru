// lol

#include <iostream>
#include <string>

int main() {
    std::string str = "02210121";
    auto i = std::stoull(str,0,3);
    std::cout << i;
} // there there, ThePhD.
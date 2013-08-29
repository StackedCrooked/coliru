#include <iostream>
#include <string>
#include <algorithm>


int main() {
    std::string s("Hello World!");
    std::reverse(s.begin(), s.end());
    std::cout << s;
}


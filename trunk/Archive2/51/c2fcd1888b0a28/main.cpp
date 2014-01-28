#include <iostream>
#include <string> 

int main() {
    std::string s{"“test test test"};
    std::cout << s << '\n';
    std::cout << s.front() << '\n';
    std::cout << s.substr(0, 3) << '\n';
}

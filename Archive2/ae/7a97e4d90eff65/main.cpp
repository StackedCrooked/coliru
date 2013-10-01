#include <iomanip>
#include <iostream>
#include <string>

int main() {
    std::string s;
    int i;
    std::cin >> s;
    std::cout << s << std::endl;
    i = std::stoi(s, 0, 0);
    std::cout << i << std::endl;
}

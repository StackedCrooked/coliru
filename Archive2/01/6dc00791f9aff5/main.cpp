#include <cassert>
#include <iostream>
#include <string>

void printReverseRecursive() {
    std::string s;
    if (std::cin >> s) {
        printReverseRecursive();
        std::cout << s << '\n';
    }
}

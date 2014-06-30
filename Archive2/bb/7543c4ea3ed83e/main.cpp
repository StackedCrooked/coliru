#include <iostream>

int main() {
    int day, month, year;
    char sep;
    std::cin >> month >> sep;
    if(sep == '/') {
        std::cin >> day >> sep >> year;
        if(sep != '/') {
            // bad
            std::cerr << "bad format\n";
        }
        std::cout << month << '/' << day << '/' << year << '\n';
    }
}
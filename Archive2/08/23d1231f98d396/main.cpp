#include <iostream>

int main() {
    std::cout << "==ROW MAJOR==" << std::endl;
    std::cout << "Column=" << 7/4 << std::endl << "Line=" << 7%4 << std::endl << std::endl; // Column = i/w Line= i%w
    std::cout << "==COLUMN MAJOR==" << std::endl;
    std::cout << "Column=" << 7/3 << std::endl << "Line=" << 7%3 << std::endl; // Column = i/h Line= i%
    return 0;
}
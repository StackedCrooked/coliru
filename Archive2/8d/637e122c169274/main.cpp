#include <iostream>
#include <sstream>

int multiplyBy10(int number)
{
    std::stringstream str;
    str << number << '0';
    str >> number;
    return number;
}

int main() {
    std::cout << (multiplyBy10(24));
}
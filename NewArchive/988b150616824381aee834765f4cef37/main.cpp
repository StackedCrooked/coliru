#include <iostream>
#include <stdexcept>

void printformat(const char* str) {
    while(*str) {
        if(*str == '%' && *(++str) != '%')
            throw std::runtime_error("Missing arguments");
        std::cout << *str++;
    }
}

template<typename T, typename... Args>
void printformat(const char* str, T value, Args... args) {
    while(*str) {
        if(*str == '%' && *(++str) != '%') {
            std::cout << value;
            printformat(str,args...);
            return;
        }
        std::cout << *str++;
    }
    throw std::logic_error("Too many arguments");
}

int main() {
    printformat("% + % = %",1,1,2);
}
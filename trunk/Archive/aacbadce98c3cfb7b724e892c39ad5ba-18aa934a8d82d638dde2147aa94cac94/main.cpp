#include <iostream>
#include <cstdlib>

void error(bool pred, const char* str) {
    if(!pred) {
        while(*str) {
            if(*str == '%' && *(++str) != '%') {
                std::cerr << "Missing an argument";
                return;
            }
            std::cerr << *str++;
        }
        std::abort();
    }
}

template<typename T, typename... Args>
void error(bool pred, const char* str, T value, Args... args) {
    if(!pred) {
        while(*str) {
            if(*str == '%' && *(++str) != '%') {
                std::cerr << value;
                error(pred,str,args...);
                return;
            }
            std::cerr << *str++;
        }
        std::cerr << "Too many arguments";
        return;
    }
}

int main() {
    error(4 == 5, "% != %",4,5);
    std::cout << "This shouldn't print";
}
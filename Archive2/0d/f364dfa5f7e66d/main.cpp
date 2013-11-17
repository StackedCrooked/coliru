#include <iostream>
#include <stdexcept>

int g(int x) { 
    if(x > 10)
        throw std::logic_error("fuck");
    return x * x;
}

int f(int y) {
    try {
        return g(y);
    }
    catch(...) {
        throw std::logic_error("fuck2");
    }
}

int main() {
    std::cout << f(10) << '\n' << f(11);
}
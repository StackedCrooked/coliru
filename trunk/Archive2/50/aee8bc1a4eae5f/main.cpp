#include <string>
#include <iostream>
template<typename T> struct X {
    template<typename Y> std::string f();
};

template<typename T> template<typename Y> std::string X<T>::f() {
    return "50 imaginary internet points please.";
}

int main() {
    std::cout << X<int>().f<int>();    
    }
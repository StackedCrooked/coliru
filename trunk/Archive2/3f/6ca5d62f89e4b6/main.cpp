#include <boost/function.hpp>
#include <iostream>

template <typename T>
void func1(T& g) {
    std::cout << 1;
}

template <typename T>
void func2(T& g) {
    std::cout << 2;
}

int main() {
    boost::function<void(int)> f;
    int k;
    std::cin >> k;
    if (k == 1)
        f = func1 < int > ;
    else
        f = func2 < int > ;
}
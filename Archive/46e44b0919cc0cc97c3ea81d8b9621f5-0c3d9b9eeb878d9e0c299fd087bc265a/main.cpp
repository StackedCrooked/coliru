#include <iostream>

template<typename T>
auto f(T n){    
    struct h
    {
        h(int& n) : n(-n) { }
        h(long n) : n(n) { }
        operator int() const { return n; }
        int n;
    };
    return h(n);
}   

int main()
{
    std::cout << f(f(42));
}
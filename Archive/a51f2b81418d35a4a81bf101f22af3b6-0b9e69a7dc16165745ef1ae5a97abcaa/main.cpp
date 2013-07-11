#include <iostream>

template<typename T>
auto f(T n){    
    struct Helper
    {
        Helper(int& n) : n(-n) { }
        Helper(long n) : n(n) { }
        operator int() const { return n; }
        int n;
    };
    return Helper(n);
}   

int main()
{
        std::cout << f(f(42)) << std::endl;
}
#include <algorithm>
#include <iostream>
#include <vector>

struct X{}x;

template<typename T>
struct curry_equal
{
    curry_equal(T t) : t_(t) {}
    bool operator()(T x) { return t_ == x; }
    T t_;
};

template<typename T>
curry_equal<T> operator==(X, T t)
{
    return curry_equal<T>(t);
}

int main()
{
    std::vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    
    std::cout << *std::find_if(v.begin(), v.end(), x == 2) << std::endl;
}
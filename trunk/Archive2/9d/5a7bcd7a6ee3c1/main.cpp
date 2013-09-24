#include <iostream>

struct A
{
    int a_;
    friend auto operator==(A const& L, A const& R) 
    { 
        return L.a_ == R.a_;
    }
};

template<class T>
struct B
{
    int b_;
    friend auto operator==(B const& L, B const& R) 
    { 
        return L.b_ == R.b_;
    }
};

using BI = B<int>;

int main()
{
    std::cout << (A{1} == A{2}) << "\n";    // OK for Clang, ERROR for g++
    std::cout << (BI{1} == BI{2}) << "\n";  // ERROR for both Clang and g++
}
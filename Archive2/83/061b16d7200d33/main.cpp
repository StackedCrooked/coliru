#include <iostream>

class A{};

template <typename T>
inline T const& max (T const& a, T const& b)
{
    std::cout << "template" << '\n';
    return a;
}

template <typename T>
inline T const& max (T const& a, T const& b, T const& c)
{
    return max (max(a,b), c);
}

inline A const& max (A const& a, A const& b)
{
    std::cout << "non-template" << '\n';
    return b;
}

int main()
{
    A a, b, c;
   max(a, b, c);   
}
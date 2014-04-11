#include <iostream>
#include <ostream>

template <typename T>
inline T const& max (T const& a, T const& b)
{
    std::cout << "template" << '\n';
    return a < b ? b : a;
}

template <typename T>
inline T const& max (T const& a, T const& b, T const& c)
{
    return max (max(a,b), c);
}

struct foo
{
    foo(int i) : i(i) {}
    int i;
};

bool operator<(foo const& f1, foo const& f2)
{ return f1.i < f2.i; }

inline foo const& max (foo const& a, foo const& b)
{
    std::cout << "non-template" << '\n';
    return a < b ? b : a;
}

std::ostream& operator<<(std::ostream& os, foo const& f)
{ return os << f.i; }

int main()
{
    std::cout << max(foo(3), foo(5), foo(7)) << '\n';   
}

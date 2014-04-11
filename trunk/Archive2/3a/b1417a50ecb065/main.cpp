#include <iostream>

template <typename T>
inline T const& max (T const& a, T const& b)
{
    std::cout << "template" << '\n';
    return a < b ? b : a;
}

int const& max (int const& a, int const& b);

template <typename T>
inline T const& max (T const& a, T const& b, T const& c)
{
    return max (max(a,b), c);
}

inline int const& max (int const& a, int const& b)
{
    std::cout << "non-template" << '\n';
    return a < b ? b : a;
}

int main()
{
    std::cout << max(3, 5, 7) << '\n';   
}

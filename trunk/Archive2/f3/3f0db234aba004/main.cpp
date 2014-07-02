#include <iostream>

// generic code

template <typename T>
inline T const& max(T const& a, T const& b)
{
    std::cout << "template" << '\n';
    return a;
}

template <typename T>
inline T const& max(T const& a, T const& b, T const& c)
{
    using ::max; // fallback if no user-defined max
    return max(max(a, b), c);
}

// X specific code

namespace X {

class A {};

inline X::A const& max(X::A const& a, X::A const& b)
{
    std::cout << "non-template" << '\n';
    return a;
}

} // namespace X

int main()
{
    X::A a, b, c;
    max(a, b, c);
}

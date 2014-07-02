#include <iostream>

namespace X {
    class A {};
}

template <typename T>
inline T const& max(T const& a, T const& b, T const& c)
{
	return max(max(a, b), c);
}

inline X::A const& max(X::A const& a, X::A const& b)
{
    std::cout << "non-template" << '\n';
    return a;
}

int main()
{
	X::A a, b, c;
	max(a, b, c);
}

namespace X {
    template <typename T>
    inline T const& max(T const& a, T const& b)
    {
        std::cout << "template" << '\n';
        return a;
    }
}





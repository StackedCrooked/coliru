#include <iostream>

template <typename T>
struct myless
{
    constexpr bool operator()(const T &lhs, const T &rhs) const
    {
        return lhs < rhs;
    }
};

template <typename A, typename U = myless<A>> // std::less works
bool f(A a, A b, U u = U())
{
    return u(a, b);
}

int main() 
{
    std::cout << std::boolalpha;

    std::cout << f("AB/CD", "CD/AB") << '\n';
    std::cout << f(100, 10) << '\n';
}

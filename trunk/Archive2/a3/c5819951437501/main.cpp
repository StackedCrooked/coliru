#include <iostream>

struct X
{
    int a = 0;
    float b = 0;
    X &operator += (const X &rhs);
};

template <typename Callable,
          typename... Things>
void for_all_x (Callable &&callable,
                Things&&... things)
{
    callable (things.a...);
    callable (things.b...);
}

X &X::operator += (const X &rhs)
{
    for_all_x ([] (auto &p, const auto &q) { p += q; }, *this, rhs);
    return *this;
}

int main()
{
    X x;
    x.a = 1;
    x += x;
    std::cout << x.a << std::endl;
}

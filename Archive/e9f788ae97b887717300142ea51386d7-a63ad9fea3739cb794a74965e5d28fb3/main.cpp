#include <type_traits>

struct X
{
    X(float) {}
};

int const x = 3;

X f(float(x));

int main()
{
    static_assert(std::is_same<decltype(f), X(float)>::value, "!");
}

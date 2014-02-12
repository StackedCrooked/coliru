#include <type_traits>

template<typename T>
struct foo
{
    static_assert(std::is_same<int&, const T&>::value, "!");
};

foo<int&> x;

int main() {}

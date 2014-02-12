#include <type_traits>

template<typename T>
struct foo
{
    static_assert(std::is_same<const T&, int&>::value, "!");
};

int main() { foo<int&> x; }

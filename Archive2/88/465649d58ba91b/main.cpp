struct A
{
    alignas(2) char x;
};

#include <type_traits>

int main()
{
    static_assert(std::is_same<decltype(A::x), char>::value, "!");
}
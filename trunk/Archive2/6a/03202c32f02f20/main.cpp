#include <type_traits>

int main()
{
    static_assert(std::is_same<decltype(throw 42), void>::value, "!");
}
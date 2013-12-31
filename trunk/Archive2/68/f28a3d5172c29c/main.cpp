#include <type_traits>

int main()
{
    static_assert(std::is_same<int, decltype(+true)>::value, "!");
}
    
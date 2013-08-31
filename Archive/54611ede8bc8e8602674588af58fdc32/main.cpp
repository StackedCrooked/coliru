#include <iostream>
#include <type_traits>

template<typename T>
auto constexpr get(T && t) -> decltype(t)
{
    return t;
}

template<typename T>
void print_signature(T&&)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

int main()
{
    auto abc = get("abc");
    print_signature(abc);
    print_signature(std::common_type<decltype(abc)>{});
}
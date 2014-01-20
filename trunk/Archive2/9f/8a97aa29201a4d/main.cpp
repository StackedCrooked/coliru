#include <cstddef>
#include <iostream>
#include <type_traits>

template <typename... Args>
using index_sequence_for = std::integral_constant<size_t, sizeof...(Args)>;

template <typename... Args>
void fun() {
    typedef index_sequence_for<Args...> indices_type;
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    std::cout << "sizeof...(Args)                    = " << sizeof...(Args) << std::endl;
    std::cout << "index_sequence_for<>::value        = " << index_sequence_for<>::value << std::endl;
    std::cout << "index_sequence_for<Args...>::value = " << index_sequence_for<Args...>::value << std::endl;
    std::cout << "indices_type::value                = " << indices_type::value << std::endl;
}

int main()
{
    fun<>();
}
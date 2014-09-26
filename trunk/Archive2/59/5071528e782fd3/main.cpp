#include <tuple>
#include <cstdint>
#include <iostream>
#include <typeinfo>

template <typename T>
struct function_traits
    : public function_traits<decltype(&T::operator())>
{};
// For generic types, directly use the result of the signature of its 'operator()'

template <typename ClassType, typename ReturnType, typename... Args>
struct function_traits<ReturnType(ClassType::*)(Args...) const>
    // we specialize for pointers to member function
{
    enum { arity = sizeof...(Args) };
    // arity is the number of arguments.

    typedef ReturnType result_type;

    template <std::size_t i>
    struct arg
    {
        typedef typename std::tuple_element<i, std::tuple<Args...>>::type type;
        // the i-th argument is equivalent to the i-th tuple element of a tuple
        // composed of those arguments.
    };
};

namespace detail
{
template <typename T, std::size_t ... Is>
void display(std::index_sequence<Is...>)
{
    std::initializer_list<int>{((std::cout << typeid(typename T::template arg<Is>::type).name() << std::endl), 0)...};
}
}

template <typename T>
void display()
{
    detail::display<T>(std::make_index_sequence<T::arity>());
}

int main()
{
    auto lambda = [] (int i, char c) -> char { return '*'; };
    typedef function_traits<decltype(lambda)> traits;

    display<traits>();
}

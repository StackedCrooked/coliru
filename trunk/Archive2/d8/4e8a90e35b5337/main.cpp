#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <typeinfo>

template <typename...>
struct Queuer;

template <typename A>
struct Queuer<A>
{
    using type = std::tuple<A>;  
};

template <typename A, typename B, typename Enable=void>
struct Swapper;

template <typename A, typename B>
struct Swapper<A, B, typename std::enable_if<std::is_base_of<B, A>::value>::type>
{
    using type = typename std::tuple<A, B>;
};

template <typename A, typename B>
struct Swapper<A, B, typename std::enable_if<std::is_base_of<A, B>::value>::type>
{
    using type = typename std::tuple<B, A>;
};

template <typename First, typename Second, typename... Args>
struct Queuer<First, Second,  Args...>
{
    using type = typename Swapper<First, Second>::type;
};

class A {};
class B : A {};

int main()
{
    std::cout << typeid(typename Queuer<A, B>::type).name();
}

#include <type_traits>
#include <iostream>
template<typename... T>
struct make_void { typedef void type;};

template<typename... T>
using void_t = typename make_void<T...>::type;

template<typename T, typename = void>
struct is_complete : std::false_type{};

template<typename T>
struct is_complete<T, void_t<decltype(sizeof(T))>> : std::true_type{};

struct Complete{};

int main()
{
    std::cout<<is_complete<Complete>::value<<is_complete<class Incomplete>::value << '\n';
}
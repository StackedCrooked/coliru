#include <type_traits>
#include <utility>

struct X
{
    constexpr void fun() {} // OK
    constexpr auto gun() {} // OK
};

template<class T>
struct Y
{
    constexpr void fun() {} // OK
    //constexpr auto gun() {} // ERROR, why?
};

int main() 
{
    static_assert(std::is_same<void, decltype(std::declval<X>().fun())>::value, "");    
    static_assert(std::is_same<void, decltype(std::declval<X>().gun())>::value, "");    
    static_assert(std::is_same<void, decltype(std::declval<Y<int>>().fun())>::value, "");    
    //static_assert(std::is_same<void, decltype(std::declval<Y<int>>().gun())>::value, "");    
}

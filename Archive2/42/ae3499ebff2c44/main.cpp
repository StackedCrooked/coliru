#include <type_traits>
#include <utility>

struct X
{
    constexpr void fun() {}             // OK
    constexpr auto gun() {}             // OK
              auto hun() {}             // OK
    constexpr auto iun() { return 0; }  // OK
};

template<class T>
struct Y
{
    constexpr void fun() {}             // OK
  //constexpr auto gun() {}             // ERROR, why?
              auto hun() {}             // OK
    constexpr auto iun() { return 0; }  // OK
};

int main() 
{
    static_assert(std::is_same<void, decltype(std::declval<X>().fun())>::value, "");    
    static_assert(std::is_same<void, decltype(std::declval<X>().gun())>::value, "");    
    static_assert(std::is_same<void, decltype(std::declval<X>().hun())>::value, "");    
    static_assert(std::is_same<int , decltype(std::declval<X>().iun())>::value, "");    

    static_assert(std::is_same<void, decltype(std::declval<Y<X>>().fun())>::value, "");    
  //static_assert(std::is_same<void, decltype(std::declval<Y<X>>().gun())>::value, "");    
    static_assert(std::is_same<void, decltype(std::declval<Y<X>>().hun())>::value, "");    
    static_assert(std::is_same<int , decltype(std::declval<Y<X>>().iun())>::value, "");    
}

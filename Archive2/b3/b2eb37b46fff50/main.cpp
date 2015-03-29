#include<iostream>
#include <type_traits>
template<class...> struct voider { using type = void; };
template<class... T> using void_t = typename voider<T...>::type;
    
    template<class T, class = void>
    struct is_ostreamable : std::false_type{};
    
    template<class T>
    struct is_ostreamable<T, void_t<decltype(std::declval<std::ostream &>() <<
                                             std::declval<T>())>> : std::true_type {};
                                             
struct Foo;

static_assert(is_ostreamable<int>(), "");
static_assert(!is_ostreamable<Foo>(), "");

int main(){}
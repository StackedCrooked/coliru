#include <typeinfo>
#include <type_traits>
#include <array>
#include <iostream>

namespace detail {
template<class>
struct sfinae_true : std::true_type{};
    
template<class T>
struct has_get_null {
	template <typename C>
    static auto test(int) -> sfinae_true<decltype(std::declval<C>().get_null())>;
	template <typename>
    static auto test(...) -> std::false_type;
    
    using type = decltype(test<T>(0));
};
}

template <typename T>
struct has_get_null
    : detail::has_get_null<T>::type {};


struct f {
    void get_null () {};
};

struct g {};


int main () {
   
   std::cout << typeid( std::conditional<has_get_null<f>::value, int, char>::type ).name() << std::endl;
   std::cout << typeid( std::conditional<has_get_null<g>::value, int, char>::type ).name() << std::endl;
   
}
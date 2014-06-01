#include <typeinfo>
#include <type_traits>
#include <array>
#include <iostream>

typedef std::array<char, 1> sfinae_small_t;
typedef std::array<char, 2> sfinae_big_t;


namespace detail {
	template<typename T>
	struct has_get_null_function {
		template <typename C> static sfinae_small_t test( decltype( &C::get_null ) );
		template <typename C> static sfinae_big_t test( ... );

		const static bool value = sizeof( test<T>( 0 ) ) == sizeof( sfinae_small_t );
	};
}

template <typename T>
struct has_get_null_function : public std::integral_constant<bool, detail::has_get_null_function<T>::value > {

};


struct f {
    void get_null () {};
};

struct g {};


int main () {
   
   std::cout << typeid( std::conditional<has_get_null_function<f>::value, int, char>::type ).name() << std::endl;
   std::cout << typeid( std::conditional<has_get_null_function<g>::value, int, char>::type ).name() << std::endl;
   
}
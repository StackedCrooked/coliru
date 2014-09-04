#include <type_traits>
struct foo {

    template<class T>
	foo(T , typename std::enable_if<std::is_integral<T>::value>::type * = nullptr) { }
	template<class T>
	foo(T , typename std::enable_if<std::is_floating_point<T>::value>::type * = nullptr) { }
};

struct bar : foo {
	using foo::foo;
};

int main() { }
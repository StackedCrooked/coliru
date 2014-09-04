#include <type_traits>
#include <iostream>
struct foo {

    template<class T>
	foo(T , typename std::enable_if<std::is_integral<T>::value>::type * = nullptr) { std::cout << "integral" << std::endl; }
	template<class T>
	foo(T , typename std::enable_if<std::is_floating_point<T>::value>::type * = nullptr) { std::cout << "floating" << std::endl; }
};

struct bar : foo {
	using foo::foo;
};

int main() {
    bar b(1, 0);
    bar bb(1.0, 0);
}
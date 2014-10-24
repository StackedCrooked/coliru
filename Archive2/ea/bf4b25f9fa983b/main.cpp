#include <iostream>
#include <string>
#include <type_traits>
#include <utility>

template<typename...>
using void_t = void;

template<typename T, typename... Us>
using constructible_t = decltype(T(std::declval<Us>()...));

template<typename... Us>
struct TypeList {};

template<typename, typename, typename = void>
struct is_constructible_helper : std::false_type {};

template<typename T, typename... Us>
struct is_constructible_helper<T, TypeList<Us...>, void_t<constructible_t<T, Us...>>> : std::true_type{};

template<typename T, typename... Args>
struct is_constructible : is_constructible_helper<T, TypeList<Args...>> {};


struct Foo {
	Foo() {};
	Foo(int i) {};
	Foo(double, std::string) {}
};

int main() {
	static_assert(is_constructible<Foo>::value, "Foo()");
    static_assert(!is_constructible<Foo, std::string>::value, "Foo(std::string)");
	static_assert(is_constructible<Foo, int>::value, "Foo(int)");
	static_assert(is_constructible<Foo, float>::value, "Foo(float)");
    static_assert(is_constructible<Foo, double, std::string>::value, "Foo(float)");
    std::cout << __clang_major__ << "." << __clang_minor__ << "." << __clang_patchlevel__ << std::endl;
}

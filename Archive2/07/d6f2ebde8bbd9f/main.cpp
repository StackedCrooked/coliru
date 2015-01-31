#include <iostream>
#include <type_traits>
#include <typeinfo>
#include <cxxabi.h>

template <class T>
struct My
{
    template<class C>
	static typename std::enable_if<std::is_integral<C>::value, long long>::type f(C*);
	
	template<class>
	static long double f(...);
	
	typedef decltype(f<T>(0)) type;
};

int main() {

    auto myInt = typeid(My<int>::type).name();
    auto myDouble = typeid(My<double>::type).name();

    std::cout << abi::__cxa_demangle(myInt, 0, 0, 0) << std::endl;
    std::cout << abi::__cxa_demangle(myDouble, 0, 0, 0) << std::endl;

	return 0;
}
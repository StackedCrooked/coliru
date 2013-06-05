#include <iostream>

#include <type_traits>

struct X {

    template<typename T, typename = typename std::enable_if<std::is_same<typename std::remove_cv<T>::type,int>::value>::type>
	X(std::initializer_list<T>) { std::cout << "list" << std::endl; }
	X(float) { std::cout << "float" << std::endl; }
};

int main() {
	X a(1);		// float (implicit conversion)
	X b{1};		// list
	X c(1.0f);	// float
	X d{1.0f};	// list (narrowing conversion) ARG!!!

	// warning: narrowing conversion of '1.0e+0f' from 'float' to 'int'
	// inside { } [-Wnarrowing]
}

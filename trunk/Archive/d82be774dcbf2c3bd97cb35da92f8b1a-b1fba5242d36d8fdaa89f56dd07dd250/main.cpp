#include <iostream>

#include <type_traits>

struct X {

    template<typename T, typename = typename std::enable_if<std::is_same<T,int>::value>::type>
	X(std::initializer_list<T>) { std::cout << "list" << std::endl; }
	X(float) { std::cout << "float" << std::endl; }
};

int main() {
	X a(1);		// float (implicit conversion)
	X b{1};		// list
	X c(1.0f);	// float
	X d{1.0f};	// float (yay)
}

#include <iostream>
#include <typeinfo>

void overloaded(int);
void overloaded(void);

template<typename ...P, typename R>
auto deduce(R (P...)) -> R (&&)(P...);

template<typename ...P>
using full_type = typename std::remove_reference<
   decltype(deduce<P...>(&overloaded))>::type;


int main() {
    std::cout << typeid(
		full_type<int>
		).name() << std::endl;

	return 0;
}
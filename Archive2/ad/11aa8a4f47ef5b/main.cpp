#include <iostream>

template<typename T>
void f(T);

template<>
void f<int>(int) { std::cout << "chose int\n"; }

template<>
void f<int&>(int&) { std::cout << "chose int&\n"; }

template<>
void f<const int>(const int) { std::cout << "chose const int\n"; }

template<>
void f<volatile int>(volatile int) { std::cout << "chose volatile int\n"; }

int main()
{
    std::cout << "implicit int: ";
	int a = 0;
	f(a);

	std::cout << "implicit int&: ";
	int& b = a;
	f(b);

	std::cout << "implicit const int: ";
	const int c = 0;
	f(c);

	std::cout << "implicit volatile int: ";
	volatile int d = 0;
	f(d);

	std::cout << "explicit int: ";
	f<int>(a);

	std::cout << "explicit int&: ";
	f<int&>(b);

	std::cout << "explicit const int: ";
	f<const int>(c);

	std::cout << "explicit volatile int: ";
	f<volatile int>(d);
}

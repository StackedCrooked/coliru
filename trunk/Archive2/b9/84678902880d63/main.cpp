#include <iostream>

// Either of these overloaded functions will work (but both together would create an ambiguous overload).
void g(int) { std::cout << "g() chose int\n"; }
// void g(const int&) { std::cout << "g() chose const int&\n"; }

// Only the first of these template specializations can be implicitly instantiated.
// Explicit instantiation is required to use the second specialization.
template<typename T>
void f(T);

// template<>
// void f<int>(int i) { std::cout << "f() chose int\n"; ++i; }

template<>
void f<const int&>(const int&) { std::cout << "f() chose const int&\n"; }

int main()
{
    int a = 0;
	const int& b = a;

	g(a);
	g(b);
	f(a);
	f(b);
}
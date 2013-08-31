#include <iostream>

typedef int foo;

struct A {
    // oops name clash (member function instead of type)
	// VC120: instead of failing compilation set_something is called with the return value of foo()
	// GCC/Clang: compilation fails "error: expected ‘)’ before ‘{’ token"
	A() { set_something(foo{}); }

	int foo() { std::cout << "foo()\n"; return 10; }

	template <typename T>
	void set_something(T&& value) { std::cout << "bar(" << value << ")\n"; }
};

int main()
{
	// Visual Studio 2013 Preview compiles and prints:
	// foo()
	// bar(10)
	A a;
}
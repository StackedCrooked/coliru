#include <iostream>

using namespace std;

namespace X {

    struct A {};

}

namespace Y { // functor-style

	template<typename T>
	struct H;

	template <typename T>
	void h(T x) { H<T>()(x); }

	template<typename T>
	void f(T x) { h(x); }

	void g() { f(X::A{}); }

	template<>
	struct H<X::A>
	{
		void operator()(X::A) { cout << "Hello, world!	" << endl; }
	};

}


int main ()
{
	Y::g();
}

#include <iostream>

using namespace std;

namespace X {

    struct A {};

}

namespace Y { // functor-style

	template<typename... T>
	struct H;

	template <typename... T>
	auto h(T&&... x)
    ->decltype(H<T...>()(std::forward <T>(x)...))
      { return H<T...>()(std::forward <T>(x)...); }

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

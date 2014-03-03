#include <iostream>

using namespace std;

namespace X {

    struct A {};

}

namespace Y { // function-style

	template<typename T>
	void f(T x) { h(x); }

	void g() { f(X::A{}); }

	void h(X::A) { cout << "Hello, world!" << endl; }

}

int main ()
{
	Y::g();
}

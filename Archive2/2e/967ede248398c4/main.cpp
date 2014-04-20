#include <iostream>

class B {
public:
    enum { i = 2 };
};

namespace M {
	int i = 4;
    namespace N {

		class X : public B {
            friend void f() { std::cout << i << '\n'; }
			enum { i = 1 };
        };

		void f();
    }
}


int main()
{
    M::N::f();		//	Attention, the friend function f inside class X above belongs to the innermost enclosing namespace A.
}
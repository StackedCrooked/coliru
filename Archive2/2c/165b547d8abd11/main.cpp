#include <iostream>

class B {
public:
    enum { i = 2 };
};

namespace M {
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
    M::N::f();
}
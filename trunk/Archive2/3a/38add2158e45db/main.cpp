#include <iostream>

struct A {
};

struct C {
    explicit C(A* const & a) {
		std::cout << "C(A) called" << std::endl;
	}

	C(A* const && a) {
		std::cout << "C(A&&) called" << std::endl;
	}
};

int main() {
	A a;
    A* a_ptr = &a;	
    
    C c2(a_ptr);  // < C(A*&)  -- GOOD
    C c3(new A);  // < C(A*&&) -- GOOD
    C c1(&a);     // < C(A*&&) -- BAD!
	
    return 0;
}
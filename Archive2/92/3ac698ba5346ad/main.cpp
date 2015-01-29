#include <iostream>

template <int r>
class ranged {
    unsigned x : r;
public:
	ranged(unsigned x=0) : x(x) {}
	operator unsigned() { return x; }
	ranged &operator=(unsigned t) { x = t; return *this; }
};

int main(){
	ranged<7> x = 12345;

	std::cout << x;
}


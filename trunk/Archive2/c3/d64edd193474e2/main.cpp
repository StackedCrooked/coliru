#include <iostream>

class B1 {};
class B2 {};
class B3 {};
class B4 {};
class B5 {};
class B6 {};

class C1 : B1 {};
class C2 : B1, B2 {};
class C3 : B1, B2, B3 {};
class C4 : B1, B2, B3, B4 {};
class C5 : B1, B2, B3, B4, B5 {};
class C6 : B1, B2, B3, B4, B5, B6 {};

int main() {
	std::cout << sizeof(C1) << ' ' << sizeof(C2) << ' ' << sizeof(C3) << ' '
		<< sizeof(C4) << ' ' << sizeof(C5) << ' ' << sizeof(C6) << std::endl;
}

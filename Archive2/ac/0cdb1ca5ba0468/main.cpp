#include <iostream>

struct B;
struct A
{
    A(B);
    A() = default;
};

struct B { operator A() {std::cout << "operator A, "; return {};} };

A::A(B) {std::cout << "A::A(B), ";}

int main()
{
    A(B{});
	(A)B{};
    
    B b;
    (void)A(b);
	(void)(A)b;
    
    std::cout << std::endl;
}

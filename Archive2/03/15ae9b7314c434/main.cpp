#include <iostream>
//#include "NumberTheoryAlgorithms.hxx"

struct B;
struct A
{
    A(B);
    A(A const&) {std::cout << "COPY" << std::endl;}
    A() = default;
};

struct B { operator A() {std::cerr << "operator A" << std::endl; return {};} };

A::A(B) {std::cerr << "A::A(B)" << std::endl;}

int main()
{
    A(B{});
	(A)B{};
}

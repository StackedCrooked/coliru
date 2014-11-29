#include <initializer_list>
#include <iostream>
#include <vector>

#include <cstdlib>

struct Literal
{
    int i;
	constexpr Literal(int i) : i(i) {}
	~Literal() {std::cout << i << std::endl;}
};

struct NonLiteral
{
	NonLiteral() {std::cout << "NonLiteral()" << std::endl;}
	~NonLiteral() {std::cout << "~NonLiteral" << std::endl;}
};

Literal l1(1);
NonLiteral nonliteral1;
Literal l2(2);
NonLiteral nonliteral2;
Literal l3(3);


int main()
{
}

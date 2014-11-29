#include <iostream>

struct ConstexprCtor
{
    int i;
	constexpr ConstexprCtor(int i) : i(i) {}
	~ConstexprCtor() {std::cout << i << std::endl;}
};

struct NonLiteral
{
	NonLiteral() {std::cout << "NonLiteral()" << std::endl;}
	~NonLiteral() {std::cout << "~NonLiteral" << std::endl;}
};



ConstexprCtor l1(1);

NonLiteral nonliteral1;

ConstexprCtor l2(2);

NonLiteral nonliteral2;

ConstexprCtor l3(3);


int main() {}

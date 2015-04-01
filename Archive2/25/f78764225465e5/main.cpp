template<class Class, int Class::*dataMember>
struct Reflect
{
    operator int() {return 0;}
};

class Foo
{
public:
	int bar = decltype(Reflect<Foo, &Foo::bar>{})();
};

#include <iostream>
int main() {std::cout << Foo().bar;}
#include <iostream>

//In Foo.h
class foo
{
public:
    void fooFunction();
} *fooObject;

void foo::fooFunction()
{
    std::cout << "Print stuff" << std::endl;
}

//In Main.cpp
int main()
{
	// Linker error in vs 2012 
	fooObject->fooFunction();
}
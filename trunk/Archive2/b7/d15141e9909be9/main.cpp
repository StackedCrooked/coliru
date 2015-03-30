#include <iostream>

//In Foo.h
class foo
{
public:
    void fooFunction();
};

void foo::fooFunction()
{
    std::cout << "Print stuff" << std::endl;
}

//In Main.cpp
int main()
{
    foo f;
    foo *fooObject = &f;
	fooObject->fooFunction();
}

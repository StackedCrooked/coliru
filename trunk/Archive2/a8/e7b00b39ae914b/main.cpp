#include <iostream>

//In Foo.h
class foo
{
public:
    static void fooFunction();
};

void foo::fooFunction()
{
    std::cout << "Print stuff" << std::endl;
}

void fooFunction()
{
    std::cout << "Print stuff" << std::endl;
}

//In Main.cpp
int main()
{
    // this is one way
	foo::fooFunction();
    
    // This is another way
    fooFunction();
    
    return 0;
}

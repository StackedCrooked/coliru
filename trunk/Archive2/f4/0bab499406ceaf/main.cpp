#include <iostream>
#include <string>

class Foo
{
    virtual ~Foo() = default;
};

class Bar : public Foo
{
    virtual ~Bar() { std::cout << "It's a ba." << std::endl; }

int main()
{
    Foo* foo = new Bar();
    delete foo;
    
    return 0;
}
#include <iostream>
#include <string>

class Foo
{
public:
    virtual ~Foo() = default;
};

class Bar : public Foo
{
private:
    virtual ~Bar() { std::cout << "It's a bar." << std::endl; }
};

int main()
{
    Foo* foo = new Bar();
    delete foo;
    
    return 0;
}
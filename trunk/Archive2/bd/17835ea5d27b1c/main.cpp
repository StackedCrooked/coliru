#include <iostream>
#include <string>

class Foo
{
public:
    virtual std::string myString() {}
};

int main(int argc, char ** argv)
{
    Foo * bar = new Foo;
    bar->myString();

    return 0;
}
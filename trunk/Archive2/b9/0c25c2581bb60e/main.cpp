#include <iostream>

struct Foo {};

struct Bar
{
    void Baz(Foo*);
};

void Bar::Baz(Foo* f) {}


int main()
{
    Bar b;
    
    Foo f;
    b.Baz(&f);
    
    return 0;
}
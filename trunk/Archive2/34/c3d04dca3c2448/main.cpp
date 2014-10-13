#include <iostream>

struct Foo
{
    int* p;
    Foo() { p = new int(1); }
    
    Foo& operator=(const Foo& rhs)
    {
        delete p; // what does p point to, if it was not constructed, huh?
        p = rhs.p;
        return *this;
    }
};

int main()
{
    char buffer[sizeof(Foo)];
    Foo& f = reinterpret_cast<Foo&>(*buffer);
    Foo other;
    f = other;
}

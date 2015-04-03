#include <stdio.h>
#include <string>
#include <vector>

class Foo
{
public:
    virtual void f ( int arg = 10 )
    {
        printf ( "Foo %d\n", arg );
    }
};

class Bar : public Foo
{
public:
    virtual void f ( int arg = 20 )
    {
        printf ( "Bar %d\n", arg );
    }
};

int main()
{
    // WYWOŁUJĄCYM JEST WSKAŹNIK NA FOO, WIĘC Z FOO BIERZEMY PARAMETRY DOMYŚLNE
    Bar * item0 = new Bar(); 
    Foo* item1 = item0;
    item0->f();
    item1->f();
    Bar bar;
    bar.f();
    Foo foo;
    foo.f();
}

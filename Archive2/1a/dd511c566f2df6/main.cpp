#include <cassert>

struct foo {
    int a, b, c;
    
    foo(int a, int b)
        : foo { a, b, -1 }
    {}
    
    foo(int a, int b, int c)
        : a { a }, b { b }, c { c }
    {}
};

int main()
{
    foo f { 4, 5 };
    assert( f.c == -1 );
}
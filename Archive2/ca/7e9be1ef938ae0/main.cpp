//Define to 1 to make it work
#define WORKS 0

#if WORKS
    template< typename T > struct Foo;
#else
    template< typename T >
    struct Foo {
        T t;
    };
#endif

class Bar;  //Incomplete type

void fFooBar(Foo<Bar> const & foobar) { }

void f(Foo<Bar> const & foobar) {
    fFooBar(foobar);
}

int main()
{
    
}

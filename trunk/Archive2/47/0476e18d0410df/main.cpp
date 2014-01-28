#include <iostream>

struct A
{
    int v ;
    A( int i ) : v(i) { std::cout << v << " A::constructor\n" ; }
    ~A() { std::cout << v << " A::destructor\n" ; }
};

void foobar( int i )
{
        std::cout << "foobar(" << i << ")\n" ;
        {
            A a(1) ;
            if( i > 5 ) goto label ;
            A b(2) ;
            if( i > 0 ) goto label ;
            A c(3) ;
            --i ;
        }
    label:
        --i ;
        std::cout << "..................\n" ;
}

int main()
{
    foobar(22) ;
    foobar(2) ;
    foobar(-2) ;
}

#include <iostream>

struct A
{
    const int c = 45 ; // always const
    int i = 67 ; // const in const A, non-const in non-const A
    mutable int m = 92 ; // never const

    void foo() const ; // operates on an object of type const A
    void bar() ; // operates on an object of type (non-const) A
};

void test_it( const A* ) { std::cout << "pointer to const A\n" ; }
void test_it( A* ) { std::cout << "pointer to (non-const) A\n" ; }
void test_it( const A& ) { std::cout << "const A\n" ; }
void test_it( A& ) { std::cout << "(non-const) A\n" ; }
void test_it( const int& ) { std::cout << "const int\n" ; }
void test_it( int& ) { std::cout << "(non-const) int\n" ; }

#define TEST_IT(x) { std::cout << #x ":\t" ; test_it(x) ; }

void A::foo() const
{
    std::cout << "A::foo() const => " ;
    TEST_IT(this) ;
}

void A::bar()
{
    std::cout << "A::bar() (non-const) => " ;
    TEST_IT(this) ;
}

void baz( const A& ca, A& a )
{
    TEST_IT(ca) ; // ca: const A
    TEST_IT( ca.c ) ; // ca.c: const int
    TEST_IT( ca.i ) ; // ca.i: const int
    TEST_IT( ca.m ) ; // ca.m: (non-const) int
    std::cout << "ca.foo() => " ; ca.foo() ; // ca.foo() => A::foo() const => this: pointer to const A

    std::cout << "\n\n" ;

    TEST_IT(a) ; // a: (non-const) A
    TEST_IT( a.c ) ; // a.c: const int
    TEST_IT( a.i ) ; // a.i: (non-const) int
    TEST_IT( a.m ) ; // a.m: (non-const) int
    std::cout << "a.foo() => " ; a.foo() ; // a.foo() => A::foo() const => this: pointer to const A
    std::cout << "a.bar() => " ; a.bar() ; // a.bar() => A::bar() (non-const) => this: pointer to (non-const) A
}

int main()
{
    A a ;
    baz( a, a ) ;
}

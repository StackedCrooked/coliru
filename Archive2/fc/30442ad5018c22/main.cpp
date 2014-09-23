
struct A
{
    int i ;
    A& operator+= ( int v ) { i += v ; return *this ; }
};

A operator+ ( A a, int v ) { a.i = a.i +v ; return a ; }

int foo( A a )
{
    a += 6 ;
    return a.i ; 

    /*
        leal    6(%rdi), %eax
        ret
    */
}

int bar( A a )
{
    a = a + 6 ;
    return a.i ; 

    /*
        leal    6(%rdi), %eax
    	ret
    */
}

int foobar( A a )
{
    A temporary_object = operator+( a, 6 ) ;
    a.operator= (temporary_object) ;
    return a.i ;

    /*
        leal    6(%rdi), %eax
        ret
    */
}

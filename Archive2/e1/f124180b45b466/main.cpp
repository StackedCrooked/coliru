template < typename T > int foo( T arg ) { return arg % 10 ; }

void bar( bool f ) // note: bar is never called
{
    if(f) foo(25) ; // fine: instantiate int foo(int)
    
    else foo(2.5) ; // *** compile-time error instantiating int foo(double) 
                    // invalid type of operand double for arg % 10
}

int main() {}
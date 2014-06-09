#include <stdio.h>

// didactic: const qualified parameter pased by value
int foo( const int arg ) 
{ 
    #ifdef TRY_ASSIGNMENT
    arg = 3 ; // *** error *** can't assign to arg 
    #endif // TRY_ASSIGNMENT
    
    return arg - 3 ; 
}

int main()
{
    puts( "this is fine" ) ;
    return foo(3) ; // fine, arg is initialised with 3 
}

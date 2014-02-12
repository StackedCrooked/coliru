#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct A { int i ; } A;

void A_constructor( void* a ) 
{ 
    A* this = a ; 
    this->i = 100 ; 
    printf( "A::A() this==%p\n", (void*)this ) ; 
}

void A_destructor( A* this ) 
{ 
    this->i = 0 ; 
    printf( "A::~A() this==%p\n", (void*)this ) ; 
}

int A_foo( A* this ) 
{ 
    printf( "A::foo() this==%p\n", (void*)this ) ; 
    return this->i ; 
}

typedef struct B /* : virtual A */ {  A* virtual_base_pointer ; int j ; } B; 

void B_constructor( void* b, void* a, bool not_further_derived ) 
{ 
    if( not_further_derived ) A_constructor(a) ;
    B* this = b ; 
    this->virtual_base_pointer = a ; 
    this->j = 7777 ; 
    printf( "B::B() this==%p\n", (void*)this ) ; 
}

void B_destructor( B* this, bool not_further_derived )
{ 
    this->j = 0 ;
    printf( "B::~B() this==%p\n", (void*)this ) ;  
    if( not_further_derived ) A_destructor( this->virtual_base_pointer ) ;
}

int B_foo( B* this ) 
{ 
    printf( "B::foo() this==%p\n", (void*)this ) ; 
    return A_foo( this->virtual_base_pointer ) + this->j ; 
}

int main()
{
    char a[ sizeof(A) ] ; // memory to place the A subobject
    char b[ sizeof(B) ] ; // memory to place B
    
    B_constructor( b, a, true ) ; // construct B
    B* pb = (void*)b ;
    puts( "-------------------" ) ;
    
    int v = B_foo(pb) ; // pb->foo() ;
    printf( "B::foo returned %d\n", v ) ; 
    puts( "-------------------" ) ;
    
    A* pa = pb ? pb->virtual_base_pointer : NULL ; // A* pa = pb ;
    printf( "A* pa == %p   B* pb = %p\n", (void*)pa, (void*)pb ) ;
    puts( "-------------------" ) ;
    
    v = A_foo( pb->virtual_base_pointer ) ; // pb->A::foo()
    printf( "A::foo returned %d\n", v ) ; 
    puts( "-------------------" ) ;
    
    B_destructor(pb,true) ; // destroy B
}

#include <iostream>

struct tuna
{
    tuna( int i ) { foobar = &tuna::foo ; baz = &tuna::bar ;  v = i ; }
    
    int foo() const
    { 
        std::cout << "tuna::foo - callewd on object at address " << this << '\n' ;
        return v + 45 ;
    }
    
    int bar( int i )
    { 
        std::cout << "tuna::bar(" << i << ") - callewd on object at address " << this << '\n' ;
        v += i ;
        return v + 45 ;
    }

    int (tuna::*foobar) () const ; // pointer to member function (const)
    int (tuna::*baz) (int) ; // pointer to member function (non-const) taking an int
    
    int v ;
};

int main()
{
    int (tuna::*ptr_mem_fun)(int) = &tuna::bar ;
    
    tuna object(23), another_object(75) ;
    tuna* pointer = &another_object ;
    
    (object.*object.foobar)() ;    
    (object.*object.baz)(50) ;
    (object.*ptr_mem_fun)(60) ;
    std::cout << '\n' ;

    (another_object.*object.foobar)() ;
    (another_object.*ptr_mem_fun)(70) ;
    std::cout << '\n' ;

    (pointer->*pointer->foobar)() ;    
    (pointer->*pointer->baz)(80) ;    
    (pointer->*ptr_mem_fun)(90) ;
}

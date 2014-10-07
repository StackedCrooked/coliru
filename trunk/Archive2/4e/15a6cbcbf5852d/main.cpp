#include <iostream>
#include <string>

struct A
{
    private: int v ;

};

friend void foo( A& a )
{
    a.v = 78 ;
}

int main()
{
    const int i = 0 ;
    ++i ;
    
    ( i + 3 ; 
}

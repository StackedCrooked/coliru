#include <iostream>
#include <memory>

struct S2 {
    std::shared_ptr<int> p;
};

S2 x { std::make_shared<int>( 0 ) };

void f()
{
    S2 y =x ;                // ‘‘copy’’ x
    *y.p = 1;        
    *x.p = 2;                // change x; affects y
    y.p.reset(new int{3});   // change y; affects x
    *x.p = 4;                // change x; affects y
    
    std::cout << *y.p << ":" << *x.p << std::endl ;
}

int main()
{
    f() ;
}
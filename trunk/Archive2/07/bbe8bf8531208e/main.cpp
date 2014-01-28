#include <iostream>
#include <thread>

struct A
{
    int foo( int arg ) const { std::cout << "A::foo( " << arg << " )\n" ; return arg+2 ; }
};

int main()
{
    A object ;
    
    std::thread thread( &A::foo /* function */ , &object /* this */, 1234 /* arg */ ) ;
    thread.join() ;
    
    // object is moved to the thread
    std::thread thread2( &A::foo, std::move(object), 5678 ) ;
    thread2.join() ;
}

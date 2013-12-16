#include <vector>
#include <boost/pool/pool_alloc.hpp>
#include <memory>
#include <ctime>
#include <iostream>
#include <cstring>
#include <new>

struct A final
{
    static inline void* operator new( std::size_t )
    { return pool.allocate() ; }

    static inline void operator delete( void* p )
    { pool.deallocate( static_cast<A*>(p) ) ; }

    void tag( const char* cstr ) { std::strcpy(data,cstr) ; }
    const char* tag() const { return data ; }

    char filler[16] ;
    char data[50] ;

    static boost::fast_pool_allocator<A> pool ;
};

boost::fast_pool_allocator<A> A::pool ;

void foo( const char* current_tag ) // uses boost pool library
{
    std::unique_ptr<A> pa1( new A ) ;
    std::unique_ptr<A> pa2( new A ) ;

    A* pa3 = new A ;
    A* pa4 = new A ;

    std::cout << "objects are at: " << pa1.get() << ' ' << pa2.get() << ' '
               << pa3 << ' ' << pa4 << '\n' ;

    std::cout << "current tag: \"" << current_tag << '"' ;
    static bool first_time = true ;
    if( !first_time) std::cout << "  old tag: \"" << pa4->tag() << '"' ;
    std::cout << '\n' ;
    first_time = false ;

    std::vector< A, boost::pool_allocator<A> > seq(1000) ;
    std::cout << "objects in vector are at: " << &seq.front()
               << " to " << &seq.back() << "\n\n" ;

    pa1->tag(current_tag) ;
    pa2->tag(current_tag) ;
    pa3->tag(current_tag) ;
    pa4->tag(current_tag) ;

    delete pa4 ;
    delete pa3 ;
}

void bar() // home-grown pool with placement new (trivialized)
{
    static constexpr std::size_t MAX_OBJECTS = 1000 ;
    static char buffer[ MAX_OBJECTS * sizeof(A) ] ;

    // construct an object with placement new
    int cnt = 0 ;
    const auto new_A = [&cnt]
    {
        if( cnt == MAX_OBJECTS ) throw std::bad_alloc() ;
        return ::new (buffer + cnt++ * sizeof(A) ) A ;
    };

    // create objects
    A* array[MAX_OBJECTS] ;
    for( std::size_t i = 0 ; i<MAX_OBJECTS ; ++i ) array[i] = new_A() ;

    // use them ...

    // destroy the objects 
    for( A* ptr : array ) ptr->~A() ;
}

int main()
{
    for( const char* tag : { "one", "two", "three", "four" } )
    {
        foo(tag) ; bar() ;
        bar() ;
    }
}

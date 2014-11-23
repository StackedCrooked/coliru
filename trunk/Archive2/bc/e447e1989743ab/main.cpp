#include <utility>
#include <iostream>
#include <string>

template < typename T > struct megaptr
{
    // http://en.cppreference.com/w/cpp/utility/forward
    template< typename... CONSTRUCTOR_ARGS > megaptr( CONSTRUCTOR_ARGS&&... args )
        : ptr( new T( std::forward<CONSTRUCTOR_ARGS>(args)... ) ) {}

    T& operator*() { return *ptr ; }
    T* operator-> () { return &**this ; }

    // ...

    private: T* ptr ;
};

int main()
{
    megaptr<std::string> p1, p2( "hello world!" ), p3( 23, '!' ) ;
    std::cout << '\'' << *p1 << "'    size: " << p1->size() << '\n'
              << '\'' << *p2 << "'    size: " << p2->size() << '\n'
              << '\'' << *p3 << "'    size: " << p3->size() << '\n' ;
}

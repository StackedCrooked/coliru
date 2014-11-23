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
    megaptr<std::string> p( 12, '!' ) ;
    std::cout << *p << "\nsize: " << p->size() << '\n' ;
}

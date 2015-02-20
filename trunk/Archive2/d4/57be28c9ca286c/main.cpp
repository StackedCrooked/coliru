#include <iostream>

namespace std_as_of_now
{
    template< class T > void swap( T&, T& ) { /* ... */ } // may be overloaded
}

namespace std_with_fancy_swap // may be specialised
{
    template< class T > struct swap
    {
        void operator() ( T&, T& ) const { /* ... */ }
    };
}

namespace A
{
    struct B { /* ... */ } ;

    struct swap_helper
    {
        static void swap( B&, B& ) { /* ... */ std::cout << "custom swap\n" ; }
    };
}

namespace std_as_of_now
{
    void swap( A::B& a, A::B& b ) { A::swap_helper::swap(a,b) ; }
}

namespace std_with_fancy_swap
{
    template<> struct swap<A::B&>
    {
        void operator() ( A::B& a, A::B& b ) const { A::swap_helper::swap(a,b) ; }
    };
}

int main()
{
    A::B one, two ;
    
    std_as_of_now::swap( one, two ) ; // custom swap
    
    std_with_fancy_swap::swap<A::B&>()( one, two ) ; // custom swap
}

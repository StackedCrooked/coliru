#include <iostream>
#include <string>
#include <cstddef>
#include <algorithm>

#ifdef _MSC_VER // Microsoft
   #define noexcept
   #define constexpr  
#endif   

#ifdef __GNUG__ // LLVM or GNU
   #if ! defined __clang__ // not LLVM, must be GNU
       #error "this won't work with the non-conforming GNU library" 
   #endif 
#endif

template < typename T > struct my_allocator
{
    using value_type = T ;

    my_allocator() noexcept = default ;
    template < typename U > my_allocator( const my_allocator<U>& ) noexcept {}
    template < typename U > my_allocator<T>& operator= ( const my_allocator<U>& ) noexcept { return *this ; }
    template < typename U > my_allocator( my_allocator<U>&& ) noexcept {}
    template < typename U > my_allocator<T>& operator= ( my_allocator<U>&& ) noexcept { return *this ; }
    ~my_allocator() noexcept = default ;

    // replace these with your own allocate / deallocate functions
    T* allocate( std::size_t n ) const { return static_cast<T*>( ::operator new( sizeof(T) * n ) ) ; }
    void deallocate( T* ptr, std::size_t ) const { ::operator delete(ptr) ; }
};

template < typename T, typename U >
constexpr bool operator== ( const my_allocator<T>&, const my_allocator<U>& ) { return true ; }

template < typename T, typename U >
constexpr bool operator!= ( const my_allocator<T>&, const my_allocator<U>& ) { return false ; }

int main()
{
    using my_string = std::basic_string< char, std::char_traits<char>, my_allocator<char> > ;

    my_string str = "abracadabra" ;
    std::cout << str << '\n' ;
    
    std::sort( str.begin(), str.end() ) ;
    str.erase( std::unique( str.begin(), str.end() ), str.end() ) ;
    std::cout << str << '\n' ;
}

#include <iostream>
#include <memory>

template < typename T >
T* allocate_from_raw_storage( void*& ptr, std::size_t& available )
{
    const std::size_t available_before = available ;
    
    // http://en.cppreference.com/w/cpp/memory/align
    if( std::align( alignof(T), sizeof(T), ptr, available ) == nullptr )
        throw "not enough memory" ;

    if( available_before - available ) 
        std::cout << available_before - available << " bytes were used for alignment and " ;   
    std::cout << sizeof(T) << " bytes were used for the object\n" ;    
    
    T* p = reinterpret_cast<T*>(ptr) ;
    ptr = static_cast<char*>(ptr) + sizeof(T) ;
    available -= sizeof(T) ;
    return p ;
}

int main()
{
    const std::size_t BUFFSZ = 1000 ;
    void* buffer = new char[BUFFSZ]{} ;

    void* next = buffer ;
    std::size_t szavail = BUFFSZ ;
    std::cout << "   next available address: " << next << "   bytes remaining: " << szavail << "\n\n" ;

    int* pi = allocate_from_raw_storage<int>( next, szavail ) ;
    std::cout << "pi: " << pi << "   next available address: " << next << "   bytes remaining: " << szavail << "\n\n" ;

    double* pd = allocate_from_raw_storage<double>( next, szavail ) ;
    std::cout << "pd: " << pd << "   next available address: " << next << "   bytes remaining: " << szavail << "\n\n" ;

    short* ps = allocate_from_raw_storage<short>( next, szavail ) ;
    std::cout << "ps: " << ps << "   next available address: " << next << "   bytes remaining: " << szavail << "\n\n" ;

    struct alignas(16) A { int a[4] ; };
    A* pa = allocate_from_raw_storage<A>( next, szavail ) ;
    std::cout << "pa: " << pa << "   next available address: " << next << "   bytes remaining: " << szavail << "\n\n" ;
}

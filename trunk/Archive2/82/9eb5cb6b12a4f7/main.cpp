#include <iterator>
#include <iostream>

namespace detail_
{
    template < typename CNTR > auto rbegin( CNTR& cntr ) -> decltype( cntr.rbegin() ) 
    { return cntr.rbegin() ; }
    
    template < typename CNTR > auto rbegin( const CNTR& cntr ) -> decltype( cntr.rbegin() ) 
    { return cntr.rbegin() ; }
    
    template< typename T, std::size_t N > std::reverse_iterator<T*> rbegin( T (&a)[N] ) 
    { return std::reverse_iterator<T*>( std::end(a) ) ; }
    
    template < typename CNTR > auto rend( CNTR& cntr ) -> decltype( cntr.rend() ) 
    { return cntr.rend() ; }
    
    template < typename CNTR > auto rend( const CNTR& cntr ) -> decltype( cntr.rend() ) 
    { return cntr.rend() ; }
    
    template< typename T, std::size_t N > std::reverse_iterator<T*> rend( T (&a)[N] ) 
    { return std::reverse_iterator<T*>( std::begin(a) ) ; }
    
    // note: the above would be available (in namespace std) in C++14
    
    template < typename RANGE > struct reverse_
    {
        RANGE& range ;
        reverse_( RANGE& r ) : range(r) {}
        
        auto begin() -> decltype( rbegin(range) ) { return rbegin(range) ; }  
    
        auto end() -> decltype( rend(range) ) { return rend(range) ; }  
    };
}

template < typename RANGE > detail_::reverse_<RANGE> reverse( RANGE& r ) 
{ return detail_::reverse_<RANGE>(r) ; }

int main()
{
    int a[] = { 0, 1, 2, 3, 4, 5, 6 } ;
    
    for( auto i : a ) std::cout << i << ' ' ;
    std::cout << '\n' ;

    for( auto i : reverse(a) ) std::cout << i << ' ' ;
    std::cout << '\n' ;
}

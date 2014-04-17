#include <functional>
#include <type_traits>
#include <memory>
#include <iostream>

template < typename T, typename U > 
void do_compare_( const std::reference_wrapper<T>& a, const std::reference_wrapper<U>& b, const char* a_tag, const char* b_tag )
{
    if( std::is_same< typename std::remove_cv<T>::type, typename std::remove_cv<U>::type >::value )
    {
        if( std::addressof(a) == static_cast<const volatile void*>( std::addressof(b) ) ) 
            std::cout << a_tag << " and " << b_tag << " are the same object\n" ;
            
        else if( std::addressof( a.get() ) == std::addressof( b.get() ) ) 
            std::cout << a_tag << " and " << b_tag << " are different objects, but they wrap references to the same object \n" ;
            
        else if( a == b )
            std::cout << a_tag << " and " << b_tag<< " wrap reference to two different objects which compare aqual\n" ;
    }
}

#define compare(a,b) do_compare_( a, b, #a, #b ) 

int main()
{
    int i = 7 ;
    int j = 7 ;
    
    auto a = std::ref(i) ; 
    const auto& b = a ;
    auto c = std::ref(i) ;
    auto d = std::ref(j) ;
    
    const auto e = std::cref(i) ;
    auto f = std::cref(j) ;
    
    compare(a,b) ; // a and b are the same object
    compare(a,c) ; // a and c are different objects, but they wrap references to the same object
    compare(a,d) ; // a and d wrap reference to two different objects which compare aqual
    compare(a,e) ; // a and e are different objects, but they wrap references to the same object 
    compare(a,f) ; // a and e wrap reference to two different objects which compare aqual
}

#include <utility>
#include <type_traits>

// type with the tag to indicate that it is suitable
struct gpio_class {
   typedef void is_gpio_class;
};

// fallback match gives an error
template< class P, bool is_lvalue, class dummy = void > 
struct invert_x {
    static_assert( sizeof( P ) == 0, "no match" );  
};

// this should match an lvalue
template< class P >
struct invert_x< P, true, typename P::is_gpio_class > : public gpio_class {
   constexpr invert_x( P & pin ) {}   
};

// this should match an rvalue
template< class P >
struct invert_x< P, false, typename P::is_gpio_class > : public gpio_class {
   constexpr invert_x( P && pin ) {}   
};

// 'factory' function that dispatches to the correct specialization
template< typename P >
invert_x< typename std::remove_reference<P>::type, std::is_lvalue_reference<P>{} >
invert( P && pin )
{
    return invert_x< typename std::remove_reference<P>::type, std::is_lvalue_reference<P>{} >( std::forward<P>(pin) );
}

int main()
{
    gpio_class pin4;   

    auto led1 = invert( pin4 );
    
    auto led2 = invert( gpio_class{} );
    
    (void)((void)led1, led2);
}

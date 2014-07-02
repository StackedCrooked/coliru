#include <iostream>

    template<typename T>
    struct value_category {
        // Or can be an integral or enum value
        static constexpr auto value = "prvalue";
    };
    
    template<typename T>
    struct value_category<T&> {
        static constexpr auto value = "lvalue";
    };
    
    template<typename T>
    struct value_category<T&&> {
        static constexpr auto value = "xvalue";
    };
    
    // Double parens for ensuring we inspect an expression,
    // not an entity
    #define VALUE_CATEGORY(expr) value_category<decltype((expr))>::value

int main()
{
    int x = 10, y = 2 ;
    int &xr = x ;
    int &yr = y ;
    
    std::cout << VALUE_CATEGORY( x << y ) << std::endl ;
    std::cout << VALUE_CATEGORY( 10 << 2 ) << std::endl ;
    std::cout << VALUE_CATEGORY( xr << yr ) << std::endl ;
    
    std::cout << VALUE_CATEGORY( x | y ) << std::endl ;
    std::cout << VALUE_CATEGORY( 10 | 2 ) << std::endl ;
    
    std::cout << VALUE_CATEGORY( x ^ y ) << std::endl ;
    std::cout << VALUE_CATEGORY( 10 ^ 2 ) << std::endl ;
    
    std::cout << VALUE_CATEGORY( sizeof( int ) ) << std::endl ;
    std::cout << VALUE_CATEGORY( sizeof( x ) ) << std::endl ;
    
}
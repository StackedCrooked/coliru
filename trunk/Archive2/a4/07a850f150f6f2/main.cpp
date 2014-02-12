#include <iostream>
#include <type_traits>
#include <cstdlib>

struct alignas(8) big
{
   int array [42*16];
};

big foo() ;

int main()
{
    std::srand(123456) ;
    
    std::cout << std::boolalpha
              << std::is_trivial<big>::value << '\n' // true
              << std::is_trivially_copy_constructible<big>::value << '\n' // true
              << std:: is_trivially_move_constructible<big>::value << '\n' // true
              << std::is_trivially_copy_assignable<big>::value << '\n' // true
              << std:: is_trivially_move_assignable<big>::value << '\n' ; // true
    
    
    int x = 0 ;
    for( int i = 0 ; i < 1000*1000 ; ++i ) x += foo().array[0]%2 ;
    std::cout << x << '\n' ; // statistically expected value: 1000 * 500
}

#include <iostream>
#include <type_traits>

template <typename TFx, typename T, typename... Args>
auto call_member_fn ( T& object, Args&&... args )
-> decltype( (object.*???)( std::forward<Args>( args )... ) ){
     return (object.*???)( std::forward<Args>( args )... );
}
 
struct A {
    int arf () {
        return 0;
    }
};
 
int main() {
    A a;
   std::cout << call_member_fn<decltype( &A::arf ), A>( a ) << std::endl;
    
}
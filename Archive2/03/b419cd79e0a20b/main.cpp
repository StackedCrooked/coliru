#include <iostream>
#include <type_traits>

template <typename TFx, typename T, typename... Args>
auto call_member_fn ( T& object, Args&&... args )
-> decltype( (object.*(TFx()))( std::forward<Args>( args )... ) ){
     TFx p = TFx();
     return (object.*p)( std::forward<Args>( args )... );
}
 
struct A {
    int arf () {
        return 0;
    }
};
 
int main() {
    A a;
    typedef decltype( &A::arf ) mf;
   std::cout << call_member_fn<mf, A>( a ) << std::endl;
    
}
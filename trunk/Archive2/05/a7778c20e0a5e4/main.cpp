#include <iostream>
#include <type_traits>

template <typename TFx, typename T, typename... Args>
auto call_member_fn ( T& object, TFx&& f, Args&&... args )
-> decltype( (object.*std::forward<TFx>(f))( std::forward<Args>( args )... ) ){
     return (object.*std::forward<TFx>(f))( std::forward<Args>( args )... );
}
 
struct A {
    int x = 10;
    void operator()(int y) {
        x += y;
    }
};
 
int main() {
    A a;
   call_member_fn( a, &A::operator(), 10);
   std::cout << a.x;    
}
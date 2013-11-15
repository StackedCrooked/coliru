#include <iostream>
#include <functional>

struct non_copyable_class
{
    non_copyable_class( int i = 0 ) : x(i) {}
    non_copyable_class( const non_copyable_class& ) = delete ;
    non_copyable_class( non_copyable_class&& ) = delete ;

    int x ;
};

void foo( std::reference_wrapper<non_copyable_class> w )
{
    std::cout << w.get().x << ' ' << &w.get() << '\n' ;
}


int main()
{
   non_copyable_class nc(1234) ;

   std::reference_wrapper<non_copyable_class> wrapper(nc) ;
   std::cout << &nc << ' ' << &wrapper.get() << '\n' ;
   foo(nc) ;

   non_copyable_class nc2(99) ;
   wrapper = nc2 ; // now wraps nc2
   std::cout << &nc2 << ' ' << &wrapper.get() << '\n' ;
}

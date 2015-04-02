#include <tuple>
#include <iostream>

struct X {
   struct Y {
   };
   int val;
   const int v = 10;
};

// auto constexpr reflect = make_tuple( typedef<X> );

// expande para
auto constexpr reflect = std::make_tuple( (X::Y*)nullptr, &X::val, (const int)10 );

int main() {
   
   static_assert( std::get<0>(reflect) == nullptr, "problem" );
   static_assert( std::get<1>(reflect) == &X::val, "problem" ); // verifica se o valor é o do ponteiro
   
   X x;
   x.val = 100;
   auto ptr = std::get<1>(reflect);
   
   std::cout << x.*ptr  << std::endl;
   
   return 0;
}

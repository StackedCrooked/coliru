#include <type_traits>
#include <utility>

template<typename Lambda>
struct container_version {
  Lambda closure;
  container_version( container_version const& ) = default;
  container_version( container_version && ) = default;
  container_version( container_version & ) = default;

  template<typename U>
  container_version( U&& func ):closure(func) {};

  // lets make this work on any iterable range:
  template<typename Container>
  void operator()( Container&& c ) const {
    for( auto&& x:c )
      closure(x);
  }
};

template<typename Lambda>
container_version< typename std::decay<Lambda>::type >
make_container_version( Lambda&& closure ) {
  return {std::forward<Lambda>(closure)};
}

#include <vector>
#include <iostream>
#include <functional>

int main() {
   std::vector<int> my_vec = {0, 1, 2, 3};
   for (auto x:my_vec)
      std::cout << x << ",";
   std::cout << "\n";
   make_container_version( []( int& x ) { x++; })( my_vec );
   
   for (auto x:my_vec)
      std::cout << x << ",";
   std::cout << "\n";
   
   // hey look, we can store it in a `std::function` if we need to:
   std::function< void( std::vector<int>& ) > func = make_container_version( []( int& x ) { x++; } );
   
   func(my_vec);
   for (auto x:my_vec)
      std::cout << x << ",";
   std::cout << "\n";
}
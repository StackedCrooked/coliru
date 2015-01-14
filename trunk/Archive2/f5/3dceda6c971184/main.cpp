#include <vector>
#include <cstddef>

    template<class... Ts,class...Args>
    void emplace_n( std::vector<Ts...>& vec, size_t n, Args&&... args ) {
      if (vec.capacity() < vec.size() + n ) {
        vec.reserve( (std::max)(vec.capacity()*3/2, vec.size()+n) );
      }
      for (size_t i = 1; i < n; ++i) {
        vec.emplace_back(args...);
      }
      if (n)
        vec.emplace_back(std::forward<Args>(args)...);
    }

    template<class...Ts,class...Args>
    std::vector<Ts...> emplace_create_vector( size_t n, Args&&... args ) {
      std::vector<Ts...> retval;
      emplace_n( retval, n, std::forward<Args>(args)... );
      return retval;
    }
#include <iostream>
int main() {
    auto v = emplace_create_vector<int>( 3, 22 );  
    for(int x:v)
        std::cout << x << "\n";
}
#include <vector>
#include <utility>
#include <algorithm>
#include <iostream>

    template<class T, class A, class F>
    std::vector<T, A> generate_vec( size_t n, F&& f ){
      std::vector<T, A> retval;
      retval.reserve(n);
      std::generate_n( std::back_inserter(retval), n, std::forward<F>(f) );
      return retval;
    }
    // usually you don't want to bother to pass an allocator:
    template<class T, class F>
    std::vector<T> generate_vec( size_t n, F&& f ){
      return generate_vec<T, std::allocator<T>>( n, std::forward<F>(f) );
    }

int main() {
    int i = 0;
    auto v = generate_vec<int>( 10, [&]{ return i++; } );
    for (int x : v) {
        std::cout << x << '\n';
    }
}
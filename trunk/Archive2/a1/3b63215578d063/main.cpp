#include <cstddef>

template <typename T, size_t s>
struct a
{
    T x[s] ;
} ;

template <typename T>
constexpr T func() {
    a<T,3> a1 ;
  
  a1.x[0] = 10 ;
  return a1.x[0];
}


constexpr int func2() {
    a<int,3> a1 ;
  
  a1.x[0] = 10 ;
  return a1.x[0];
}


int main()
{
    //constexpr int x = func<int>();
    constexpr int x = func2();
}
#include <cstddef>

template <typename T, size_t s>
struct test
{  
     T x[s] ;
} ;

template <typename T>
constexpr T func() {
    test<T,3> test1 ;
  
  test1.x[0] = 10 ;
  return test1.x[0];
}

constexpr int func2() {
    test<int,3> test1 ;
  
  test1.x[0] = 10 ;
  return test1.x[0];
}


int main()
{
    constexpr int x = func<int>();
}
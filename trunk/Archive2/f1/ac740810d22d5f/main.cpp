
#include <type_traits>
#include <iostream>

/*    
constexpr int f(int n) {
  int r = 1;
  
  for(int i = 1; i <= n; ++i)
    r *= i; 
  
  return r;
}*/

constexpr int f(int x) {
    return 5 >> (x + 5);
}


/*
constexpr int f(int n) {
  return n + (2147483647 - 10);
}
*/
  
template<size_t N, size_t X = f(N)>
constexpr bool h(std::integral_constant<size_t, N>) {
  return true;
}

constexpr bool h(...) {
  return false;
}

template<size_t I = 0>
constexpr size_t undefined_at() {
  if( h(std::integral_constant<size_t, I>{}) )
    return undefined_at<I + 1 <= 200 ? I + 1 : 200>();
  else return I;
}

int main()
{
    std::cout << undefined_at() << std::endl;
    return 0;
}

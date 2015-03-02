#include <iostream>

template<typename T, size_t Size>
T (&map_static_array(T (&x)[Size]))[Size]
{
    for( auto && i : x )
        i += 42;
    return x;
} 


int main()
{
  int a[10] = {};
  int (&t)[10] = map_static_array(a);
  
  for( auto && i : t )
    std::cout << i << std::endl;
  
  return 0;
}
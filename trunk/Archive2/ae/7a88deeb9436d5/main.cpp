#include <iostream>

template<typename T, size_t Size>
T (&map_static_array(T (&x)[Size]))[Size]
{
    for( size_t i = 0; i < Size; ++i )
        x[i] += 42;
    return x;
} 


int main()
{
  int a[10] = {};
  int (&t)[10] = map_static_array(a);
  
  for( size_t i = 0; i < 10; ++i )
  {
      std::cout << t[i] << std::endl;
  }
  
  return 0;
}
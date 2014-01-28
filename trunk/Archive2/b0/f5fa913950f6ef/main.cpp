#include <array>
#include <cstddef>
#include <iostream>

template<std::size_t n>
class float_vec
{
private:
  std::array<float, n> underlying_array;

public:
  template<typename... Types>
  float_vec(Types... args)
    : underlying_array{{args...}}
  {
  }
  
  int get(int index) {return underlying_array[index];}
};

int main()
{
  float_vec<4> v = {1.0f, 2.0f, 3.0f, 4.0f}; // error here
  
  for (int i = 0; i < 4; ++i)
    std::cout<<v.get(i)<<" ";
}
#include <array>
#include <cstddef>

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
};

int main()
{
  float_vec<4> v = {1, 2, 3, 4}; // error here
}
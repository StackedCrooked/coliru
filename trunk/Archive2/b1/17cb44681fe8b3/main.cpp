#include <array>
#include <cstddef>

template<std::size_t N>
std::array<bool, N> operator^(const std::array<bool, N>& a, const std::array<bool, N>& b)
{
  std::array<bool, N> c;
  for(std::size_t i = 0; i<N; ++i)
    c[i] = a[i] ^ b[i];

  return c;
}

int main()
{
    std::array<bool,500> a,b,c;
    c = b ^ a;
}
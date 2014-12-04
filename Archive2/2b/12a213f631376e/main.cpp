#include <algorithm>
#include <cassert>
#include <complex>

struct D
{
  D() noexcept { }; // does not initialize val!
  D(double d) noexcept : val(d) { }
  operator double() const noexcept { return val; }
  D& operator=(double d) noexcept { val = d; return *this; }
  double val;
};

int main() {
  alignas(std::complex<D>) unsigned char space[sizeof(std::complex<D>)];
  std::fill(std::begin(space), std::end(space), 0xCC);
  auto p = ::new(space) std::complex<D>;
  p->~complex();
  assert(std::find(std::begin(space), std::end(space), 0xCC) == std::end(space));
}

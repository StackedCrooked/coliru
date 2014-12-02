#include <algorithm>
#include <cstdint>
#include <iostream>
#include <limits>
#include <random>
#include <vector>

#ifdef pack
#define P __attribute__((packed))
#else
#define P
#endif

struct foo {
  std::int64_t i;
  char c;
} P;

bool
operator < (foo x, foo y) {
  return x.i < y.i || (x.i == y.i && x.c < y.c);
}

constexpr std::size_t N = 100000000;

int
main() {
  std::cout << "sizeof(foo) == " << sizeof(foo) << '\n';
  
  std::default_random_engine engine;
  std::uniform_int_distribution<std::int64_t> i64_d{
    0, std::numeric_limits<std::int64_t>::max()
  };
  std::uniform_int_distribution<char> c_d{
    std::numeric_limits<char>::min(), std::numeric_limits<char>::max()
  };
    
  std::vector<foo> v;
  for (std::size_t i = 0; i < N; ++i)
    v.push_back({i64_d(engine), c_d(engine)});

  std::sort(v.begin(), v.end());
  std::cout << v.front().i << ", " << +v.front().c << '\n';
}

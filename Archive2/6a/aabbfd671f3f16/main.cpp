// clang++ -std=c++11 -O2 rc4.cpp && ./a.out
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <tuple>
#include <utility>

namespace security {
namespace util {
// type safety is great
template <typename T> struct wrap {
  T x;
  wrap() = default;
  wrap(T const &x) : x{x} {}
  operator T &() { return x; }
  operator T const &() const { return x; }
  wrap(wrap &&) = default;
  wrap(wrap const &) = default;
  wrap &operator=(wrap &&) = default;
  wrap &operator=(wrap const &) = default;
  ~wrap() = default;
};

using  uint8 = wrap< std::uint8_t>;
using uint16 = wrap<std::uint16_t>;
using uint32 = wrap<std::uint32_t>;
using uint64 = wrap<std::uint64_t>;
}

namespace rc4 {
template <typename = void>
inline void stream(unsigned char *s, std::size_t slen,
                   unsigned char *k, std::size_t klen) {
  using util::uint8;
  using std::swap;
  uint8 S[256];

  for (int i = 0; i < 256; ++i) {
    S[i] = i;
  }

  for (int i = 0, j = 0; i < 256; ++i) {
    j = (j + S[i] + k[i % klen]) & 0xFF;
    swap(S[i], S[j]);
  }

  for (uint8 i = 0, j = 0; slen--;) {
    i += 1;
    j += S[i];
    swap(S[i], S[j]);
    *s++ = S[(S[i] + S[j]) & 0xFF];
  }
}
}
}

// elsewhere
namespace security {
namespace util {
  template <template <typename...> class U, typename... V>
  void swap(U<V...>& x, U<V...>& y) {
    // Option #1
    // decltype(auto) t = x; x = y; y = t;
    // Option #2
    using std::tie;
    tie(x, y) = tie(y, x);
  }
}
}

#include <random>
#include <algorithm>
#include <functional>

int main() {
  using namespace std;
  unsigned char k[  32] = {0};
  unsigned char s[8192] = {0};
  random_device rd;
  generate(begin(k), end(k), ref(rd));
  security::rc4::stream(s, sizeof s, k, sizeof k);
  for (size_t i = 0; i < sizeof s; ++i) {
    printf("%02X%s", s[i], i % 8 == 7 ? "\n" : " ");
  }
}

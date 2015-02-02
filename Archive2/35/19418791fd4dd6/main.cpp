
#include <cstddef>
#include <cstdint>
#include <tuple>
#include <array>
#include <numeric>

template<typename T> 
constexpr size_t bits(T = T{}) { 
  return sizeof(T) * 8; 
}

template<typename T>
constexpr T rot(T x, unsigned c) {
  constexpr auto b = bits<T>();
  return (x >> c%b) | (x << -c%b);
}

template<typename T>
constexpr T U(T a, T b) { return a ^ b ^ ((a&b) << 1); }

// std::array is stupid, need to use this one
template<typename T, size_t N>
struct array { 
  T x_[N];
  constexpr decltype(auto) operator[](size_t i) const { return x_[i]; }
  constexpr decltype(auto) operator[](size_t i) { return x_[i]; }
};

template<typename T> 
constexpr array<unsigned, 4> get() {
  switch(bits<T>()) {
  case 32:
    return {{8, 11, 16, 31}};
  case 64:
    return {{8, 19, 40, 63}};
  default:
    throw 0;
  }
}

template<typename T>
constexpr auto G(T& a, T& b, T& c, T& d) {
  constexpr auto R = get<T>();
  a = U(a, b); d ^= a; d = rot(d, R[0]);
  c = U(c, d); b ^= c; b = rot(b, R[1]);
  a = U(a, b); d ^= a; d = rot(d, R[2]);
  c = U(c, d); b ^= c; b = rot(b, R[3]);
}


template<typename T>
constexpr auto F(array<T, 16> & S) {
  /* Column step */
  G(S[ 0], S[ 4], S[ 8], S[12]);
  G(S[ 1], S[ 5], S[ 9], S[13]);
  G(S[ 2], S[ 6], S[10], S[14]);
  G(S[ 3], S[ 7], S[11], S[15]);
  /* Diagonal step */
  G(S[ 0], S[ 5], S[10], S[15]);
  G(S[ 1], S[ 6], S[11], S[12]);
  G(S[ 2], S[ 7], S[ 8], S[13]);
  G(S[ 3], S[ 4], S[ 9], S[14]);
  return S;
}

template<typename T>
constexpr array<T, 16> IV() {
  array<T, 16> S = {{ 
     0,  1,  2,  3, 
     4,  5,  6,  7,
     8,  9, 10, 11, 
    12, 13, 14, 15
  }};
  
  for(size_t i = 0; i < 2; ++i) {
    F(S);
  }
  
  return S;
}

#include <cstdio>

int main() {
  {
      constexpr auto S = IV<uint64_t>();
      for(int i = 0; i < 16; ++i) {
          printf("0x%016lX%s", S[i], i%4==3?",\n":",");
      }
  }
  
  {
      constexpr auto S = IV<uint32_t>();
      for(int i = 0; i < 16; ++i) {
          printf("0x%08X%s", S[i], i%4==3?",\n":",");
      }
  }
}

#include <cstdint>

#include <iostream>
#include <string>
#include <vector>
#include <utility>

namespace rc4 {
  namespace detail {
    template<typename T>
    struct wrap {
      T x;
      wrap() = default;
      wrap(T const& x) : x{x} {}
      operator T&()              { return x; }
      operator T const &() const { return x; }
      template<template<typename> class U, typename V>
      friend void swap(U<V> & x, U<V> & y) {
        decltype(x) t = x;
        x = y;
        y = t;
      }
    };

    using  u8 = wrap<uint8_t>;
    using u16 = wrap<uint16_t>;
    using u32 = wrap<uint32_t>;
    using u64 = wrap<uint64_t>;
  }

  inline void stream(unsigned char * out, size_t outlen, 
                     unsigned char * k, size_t klen) {
    using namespace detail;
    u8 S[256];
    for(size_t i = 0; i < 256; ++i) {
      S[i] = i;
    }
    
    for(size_t i = 0, j = 0; i < 256; ++i) {
      j = (j + S[i] + k[i%klen])&0xFF;
      using std::swap;
      swap(S[i], S[j]);
    }
    
    for(u8 i = 0, j = 0; outlen--; ) {
      i += 1;
      j += S[i];
      using std::swap;
      swap(S[i], S[j]);
      out[i] = S[(S[i] + S[j])&0xFF];
    }
  }
}


int main()
{
    unsigned char k[16] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
    unsigned char s[4096] = {0};
    rc4::stream(s, sizeof s, k, sizeof k);
    for(auto && x : s) {
        printf("%02X ", x);
    }
}

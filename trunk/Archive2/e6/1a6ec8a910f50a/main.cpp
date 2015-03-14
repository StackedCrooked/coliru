#include <cstdint>
#include <cstring>
#include <functional>
#include <type_traits>
#include <utility>

struct deserializer {
  const std::uint8_t* in_;

  deserializer(const std::uint8_t* in) : in_{in} {}

  template <typename T>
  operator T() {
    static_assert(std::is_pod<T>(), "");
    T t;
    std::memcpy(&t, in_, sizeof(T));
    in_ += sizeof(T);
    return t;
  }
};

struct forwarder {
  template <typename F, typename...Ts>
  forwarder(F&& f, Ts&&...ts) {
    std::forward<F>(f)(std::forward<Ts>(ts)...);
  }
};

// Requires explicit specification of argument types.
template <typename...Ts, typename F>
void unpack(F&& f, const std::uint8_t* from) {
  deserializer d{from};
  forwarder{std::forward<F>(f), static_cast<Ts>(d)...};
}

// Deduce argument types from std::function
template <typename R, typename...Args>
void unpack(std::function<R(Args...)> f, const std::uint8_t* from) {
  unpack<Args...>(std::move(f), from);
}

// Deduce argument types from function pointer
template <typename R, typename...Args>
void unpack(R (*f)(Args...), const std::uint8_t* from) {
  unpack<Args...>(f, from);
}


#include <iostream>

using namespace std;

void foo1(uint8_t a, int8_t b, uint16_t c, int16_t d, uint32_t e, int32_t f, uint64_t g, int64_t h, float i, double j)
{
    cout << a << "; " << b << "; " << c << "; " << d << "; " << e << "; " << f << "; " << g << "; " << h << "; " << i << "; " << j << endl;
}

void foo2(uint8_t a, int8_t b, uint16_t c, int16_t d, uint32_t e, int32_t f, int64_t g, uint64_t h, float i, double j)
{
    cout << a << "; " << b << "; " << c << "; " << d << "; " << e << "; " << f << "; " << g << "; " << h << "; " << i << "; " << j << endl;
}

int main()
{
  uint8_t buff[512];

  {
    uint8_t *offset = buff;

    uint8_t a = '1';
    int8_t b = '2';
    uint16_t c = 3;
    int16_t d = 4;
    uint32_t e = 5;
    int32_t f = 6;
    uint64_t g = 7;
    int64_t h = 8;
    float i = 9.123456789;
    double j = 10.123456789;

    memcpy(offset, &a, sizeof(a));
    offset += sizeof(a);
    memcpy(offset, &b, sizeof(b));
    offset += sizeof(b);
    memcpy(offset, &c, sizeof(c));
    offset += sizeof(c);
    memcpy(offset, &d, sizeof(d));
    offset += sizeof(d);
    memcpy(offset, &e, sizeof(e));
    offset += sizeof(e);
    memcpy(offset, &f, sizeof(f));
    offset += sizeof(f);
    memcpy(offset, &g, sizeof(g));
    offset += sizeof(g);
    memcpy(offset, &h, sizeof(h));
    offset += sizeof(h);
    memcpy(offset, &i, sizeof(i));
    offset += sizeof(i);
    memcpy(offset, &j, sizeof(j));
  }

#ifdef USE_PTR
  unpack(foo1, buff);
#ifdef SECOND
  unpack(foo2, buff);
#endif

#else

  std::function<void (uint8_t, int8_t, uint16_t, int16_t, uint32_t, int32_t, uint64_t, int64_t, float, double)> ffoo1 = foo1;

  unpack(ffoo1, buff);
#ifdef SECOND
  std::function<void (uint8_t, int8_t, uint16_t, int16_t, uint32_t, int32_t, int64_t, uint64_t, float, double)> ffoo2 = foo2;
  unpack(ffoo2, buff);
#endif
#endif
}

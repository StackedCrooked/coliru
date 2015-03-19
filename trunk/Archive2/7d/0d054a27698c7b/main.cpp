#include <cstdint>
#include <cstring>
#include <functional>
#include <type_traits>
#include <utility>

template <typename T>
using uncvref =
  typename std::remove_cv<
    typename std::remove_reference<T>::type
  >::type;

template <typename T> struct arg_tag {};

template <typename T>
uncvref<T> unpack_arg(const std::uint8_t*& from) {
  return unpack_arg(arg_tag<uncvref<T>>{}, from);
}

template <typename T, typename std::enable_if<std::is_trivial<T>::value, int>::type = 0>
T unpack_arg(arg_tag<T>, const std::uint8_t*& from) {
  T t;
  std::memcpy(&t, from, sizeof(T));
  from += sizeof(T);
  return t;
}

struct forwarder {
  template <typename F, typename...Args>
  forwarder(F&& f, Args&&...args) {
    std::forward<F>(f)(std::forward<Args>(args)...);
  }
};

template <typename...Ts, typename F>
void unpack_explicit(F&& f, const std::uint8_t* from) {
  forwarder{std::forward<F>(f), unpack_arg<Ts>(from)...};
}

// Requires explicit specification of argument types.
template <typename...Ts, typename F>
void unpack(F&& f, const std::uint8_t* from) {
  unpack_explicit<Ts...>(std::forward<F>(f), from);
}

// Deduce argument types from std::function
template <typename R, typename...Args>
void unpack(std::function<R(Args...)> f, const std::uint8_t* from) {
  unpack_explicit<Args...>(std::move(f), from);
}

// Deduce argument types from function pointer
template <typename R, typename...Args>
void unpack(R (*f)(Args...), const std::uint8_t* from) {
  unpack_explicit<Args...>(f, from);
}


#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>

using vec_size_t = int;

template <typename T>
std::vector<T> unpack_arg(arg_tag<std::vector<T>>, const std::uint8_t*& from) {
  std::vector<T> vec;
  auto n = unpack_arg<vec_size_t>(from);
  vec.reserve(n);
  std::generate_n(std::back_inserter(vec), n, [&from]{
    return unpack_arg<T>(from);
  });
  return vec;
}

using namespace std;

void print(std::vector<double> const& vec) {
    cout << '{';
    if (vec.size()) {
        cout << vec[0];
        for (std::size_t i = 1; i < vec.size(); ++i) {
            cout << ", " << vec[i];
        }
    }
    cout << '}';
}

void foo1(uint8_t a, int8_t b, uint16_t c, int16_t d, uint32_t e, int32_t f, uint64_t g, int64_t h, float i, double j, std::vector<double> vec)
{
    cout << a << "; " << b << "; " << c << "; " << d << "; " << e << "; " << f << "; " << g << "; " << h << "; " << i << "; " << j
         << ";  ";
    print(vec);
    cout << '\n';
}

void foo2(uint8_t a, int8_t b, uint16_t c, int16_t d, uint32_t e, int32_t f, int64_t g, uint64_t h, float i, double j, std::vector<double> vec)
{
    cout << a << "; " << b << "; " << c << "; " << d << "; " << e << "; " << f << "; " << g << "; " << h << "; " << i << "; " << j
         << "; ";
    print(vec);
    cout << '\n';
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
    offset += sizeof(j);

    {
      std::vector<double> vec{3.14, 1.414, 2.783};
      vec_size_t n = vec.size();
      memcpy(offset, &n, sizeof(n));
      offset += sizeof(n);
      for (double d : vec) {
        memcpy(offset, &d, sizeof(d));
        offset += sizeof(d);
      }
    }
  }

#ifdef USE_PTR
  unpack(foo1, buff);
#ifdef SECOND
  unpack(foo2, buff);
#endif

#else

  std::function<void (uint8_t, int8_t, uint16_t, int16_t, uint32_t, int32_t, uint64_t, int64_t, float, double, std::vector<double>)> ffoo1 = foo1;
  std::function<void (uint8_t, int8_t, uint16_t, int16_t, uint32_t, int32_t, int64_t, uint64_t, float, double, std::vector<double>)> ffoo2 = foo2;

  unpack(ffoo1, buff);
#ifdef SECOND
  unpack(ffoo2, buff);
#endif
#endif
}

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


using namespace std;

void foo1(uint8_t a, int8_t b, uint16_t c, int16_t d, uint32_t e, int32_t f, uint64_t g, int64_t h, float i, double j);

template void unpack(decltype(foo1), const std::uint8_t*);

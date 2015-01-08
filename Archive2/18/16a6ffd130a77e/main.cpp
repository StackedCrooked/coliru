#include <iostream>

#include <type_traits>

template <typename T>
constexpr T static static_max_impl(T max) {
  return max;
}

template <typename T, typename ... Types>
constexpr T static static_max_impl(T max, T first, Types ... rest) {
  return (first > max) ? static_max_impl(first, rest...) : static_max_impl(max, rest...);
}

template <typename T, typename ... Types>
constexpr T static_max(T first, Types ... rest) {
  return static_max_impl(first, rest...);
}

template <typename ... Types>
struct static_max_size {
  static constexpr size_t value = static_max(sizeof(Types)...);
};

// in libc++ but not in gcc/4.8
template <std::size_t Len, typename ...Types>
struct aligned_union {
  //static constexpr std::size_t alignment_value = static_max(alignof(Types)...);
  static constexpr std::size_t alignment_value = 
    std::integral_constant<size_t, static_max(alignof(Types)...)>::value;

private:
  static constexpr std::size_t storage_size_ =
    std::integral_constant<size_t, static_max(Len, sizeof(Types)...)>::value;
public:
  struct type {
    alignas(std::integral_constant<size_t, static_max(alignof(Types)...)>::value)
            unsigned char _[storage_size_];
  };
};

struct Testing {
  aligned_union</*Len*/0, int, float, double>::type storage_;
};

int main() {
  Testing t;
  std::cout << "Hello\n";
  return 0;
}

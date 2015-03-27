#include <cstddef>
#include <type_traits>
#include <iostream>

//#define HAVE_GET_IN_LAYOUT 0

constexpr std::size_t Align(std::size_t size, std::size_t offset) {
  return (size < 0x8
              ? (offset + 0x3) & ~0x3
              : (size < 0x10 ? (offset + 0x7) & ~0x7 : (offset + 0xf) & ~0xf));
}

template <std::size_t Start, typename... Ts> struct Layout {
  static constexpr std::size_t Size = 0;
  static constexpr std::size_t Offset = Start;
  static constexpr std::size_t TotalSize = Start;
};

template <std::size_t Start, typename T, typename... Ts>
struct Layout<Start, T, Ts...>
    : public Layout<Align(sizeof(T), Start) + sizeof(T), Ts...> {
  using Type = T;
  using Base = Layout<Align(sizeof(T), Start) + sizeof(T), Ts...>;
  
  static constexpr std::size_t Size = sizeof(Type);
  static constexpr std::size_t Offset = Align(Size, Start);
  static constexpr std::size_t TotalSize = Layout<Offset + Size, Ts...>::TotalSize;

  Type value = Offset - Start; // no particular meaning, just for testing.

#if HAVE_GET_IN_LAYOUT
    template <typename U>
	U& helper (std::true_type /* correct type */) { return value; }
	template <typename U>
	U& helper (std::false_type /* incorrect type, try next base class */) { return Base::template get<U>(); }

	template <typename U>
	U& get() { return helper<U>(std::is_same<T, U>{}); }
#endif
};

template <typename... Ts> struct Result : public Layout<0, Ts...> {
#if !HAVE_GET_IN_LAYOUT
  template <typename U, std::size_t X, typename... Us>
  U &helper(Layout<X, U, Us...> *c) { return c->value; }

  template <typename U> U &get() { return helper<U>(this); }
#endif
};

int main() {
    
  std::cout << "With HAVE_GET_IN_LAYOUT = " << HAVE_GET_IN_LAYOUT << std::endl;

    
  std::cout << "layout size <> = " << Layout<0>::TotalSize << std::endl;
  std::cout << "layout size <int> = " << Layout<0, int>::TotalSize << std::endl;
  std::cout << "layout size <long> = " << Layout<0, long>::TotalSize << std::endl;
  std::cout << "layout size <int,int> = " << Layout<0, int, int>::TotalSize << std::endl;
  std::cout << "layout size <int,long> = " << Layout<0, int, long>::TotalSize << std::endl;
  std::cout << "layout size <long,int> = " << Layout<0, long, int>::TotalSize << std::endl;
  std::cout << "layout size <long,long> = " << Layout<0, long, long>::TotalSize << std::endl;

  std::cout << "get: " << Result<int, long, long double>{}.get<long>() << std::endl;
  std::cout << "-----------------------------" << std::endl;

  return 0;
}



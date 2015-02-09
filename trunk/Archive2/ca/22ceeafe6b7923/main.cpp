#include <iostream>

template<char... s>
struct chs {
  constexpr chs<'/', s...> operator!() const { return {}; }

  template<char... cs>
  constexpr chs<s...,'<',cs...,'>'> operator[](chs<cs...>) const { return {}; }

  static constexpr char const str[sizeof...(s)+1] = {s..., 0};
};

template<char... s>
constexpr char const chs<s...>::str[sizeof...(s)+1];


auto markup_start = chs<> {};
auto markup_end   = chs<> {};

auto html = chs<'h','t','m','l'> {};
auto body = chs<'b','o','d','y'> {};

int main () {
  std::cout << decltype (
    markup_start
      [html]
        [body] [!body]
      [!html]
  )::str << std::endl;
}
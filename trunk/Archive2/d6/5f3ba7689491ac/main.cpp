#include <iostream>
#include <tuple>
#include <utility>
#include <array>

// A type tag:

    template<class T>struct tag{using type=T;};
// `void_t` (coming in C++17 to a compiler near you):

    template<class...>struct voider{using type=void;};
    template<class...Ts>using void_t=typename voider<Ts...>::type;
// `enable_first_t` takes a pack of `std::enable_if` (note the lack of `_t`), and returns the first that passes the test.  You can use `tag<X>` to replace `std::enable_if<true, X>`:

    template<class T,class=void>struct has_type:std::false_type{};
    template<class T>struct has_type<T, void_t<typename T::type>>:std::true_type{};
    
    namespace details {
      template<class, class...Ts>
      struct enable_first {};
      template<class T0, class...Ts>
      struct enable_first<std::enable_if_t< !has_type<T0>{} >, T0, Ts... >:enable_first<void, Ts...> {};
      template<class T0, class...Ts>
      struct enable_first<std::enable_if_t<  has_type<T0>{} >, T0, Ts...>:T0 {};
    }
    
    template<class...Ts>using enable_first_t=typename details::enable_first<void, Ts...>::type;

    template<class T>
    using result = enable_first_t<
      std::enable_if<sizeof(T)==sizeof(char), char>,
      std::enable_if<sizeof(T)==sizeof(short), short>,
      std::enable_if<sizeof(T)==sizeof(long), long>,
      tag<int>
    >;
// this behaves a lot like a `switch`, but the statements are full boolean expressions.

int main() {
    result<char> c = 'a';
    std::cout << c << '\n';
    result<int> x = 3;
    std::cout << x << '\n';
}
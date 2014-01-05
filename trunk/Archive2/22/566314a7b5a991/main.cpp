#include <type_traits>

template<bool...   > struct all_of : std::true_type {};
template<bool... Bs> struct all_of<true,  Bs...> : all_of<Bs...> {};
template<bool... Bs> struct all_of<false, Bs...> : std::false_type {};

template<typename T, typename... Ts>
using all_is = all_of<std::is_same<T, Ts>::value ...>;

template<typename T>
using remove_reference_t = typename std::remove_reference<T>::type;

template<typename T>
struct Obj {
  template<typename... Args>
  Obj (Args&&... args) {
    static_assert (all_is<T, remove_reference_t<Args> ...>::value, "!!");

    // std::forward whatever you want, reference correctness maintained
    // while still only accepting Ts
  }
};

int
main (int argc, char *argv[])
{
  Obj<int> { 1, 2,     3 }; // legal
  Obj<int> { 1, 2, 3.14f }; // error
}
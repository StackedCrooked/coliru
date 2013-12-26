#include <iostream>
#include <type_traits>

struct wrap_base {};

template<typename T>
struct wrap : wrap_base {};

// -------------------------------------------------------------------

struct no_wrap_bases_tag   {};
struct gief_wrap_bases_tag {};

template<
  typename T,
  int (*R1) [std::is_base_of<wrap_base, T>::value == false ] = nullptr,
  int (*R2) [std::is_same<decltype (decltype (R1) {}, func (std::declval<wrap<T>> ())), gief_wrap_bases_tag>::value == true ] = nullptr

  // equivalent ruling that works, but only because clang happens to evaluate type template parameters in the order they appear
  //typename B = typename std::enable_if< std::is_base_of<wrap_base, T>::value == false, int>::type,
  //typename std::enable_if<std::is_same<decltype (std::declval<B> (), func (std::declval<wrap<T>> ())),gief_wrap_bases_tag>::value>::type * = nullptr
>
no_wrap_bases_tag func (T) {
  std::cerr << "no_wrap_bases_tag func (T)\n";
  func (wrap<T> {});
  return {};
}

template<
  typename T,
  int (*) [std::is_base_of<wrap_base, T>::value == true ] = nullptr
>
gief_wrap_bases_tag func (T) {
  std::cerr << "gief_wrap_bases_tag func (T)\n";
  return {};
}

int
main (int argc, char *argv[])
{
  func (123);
}
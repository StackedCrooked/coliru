#include <iostream>
#include <iterator>
#include <string>

template<typename T>
struct has_const_iterator {
  template<typename C> static char test(const typename C::const_iterator*);
  template<typename C> static long test(...);
  static const bool value = sizeof(test<T>(0)) == sizeof(char);
  typedef T type;
};

template <typename T>
struct has_begin_end {
  struct Dummy { typedef void const_iterator; };
  typedef typename std::conditional<has_const_iterator<T>::value, T, Dummy>::type TCompatible;
  typedef typename TCompatible::const_iterator TIter;

  struct Fallback { TIter begin() const; TIter end() const; };
  struct Derived : public TCompatible, public Fallback { };

  template<typename C, C> struct TWapper;

  template<typename C> static char b(TWapper<TIter (Fallback::*)() const, &C::begin>*);
  template<typename C> static long b(...);
  template<typename C> static char e(TWapper<TIter (Fallback::*)() const, &C::end>*);
  template<typename C> static long e(...);

  static bool const beg_value = sizeof(b<Derived>(0)) == sizeof(long);
  static bool const end_value = sizeof(e<Derived>(0)) == sizeof(long);
};

template<typename T>
struct is_container {
  static const bool value = has_const_iterator<T>::value &&
      // !std::is_same<char, typename T::const_iterator::value_type>::value &&
      has_begin_end<T>::beg_value && has_begin_end<T>::end_value;
};

int main(int argc, char* argv[]) {
  std::cout << std::boolalpha << is_container<std::string>::value << std::endl;
}
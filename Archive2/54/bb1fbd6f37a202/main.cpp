#include <type_traits>

template<
  typename T,
  int(*)[ std::is_enum<T>::value ] = nullptr
>
typename std::underlying_type<T>::type
get_underlying_value (T value) {
  return { /* ... */ };
}

int 
main (int argc, char *argv[])
{
  enum class E : int { A, B, C };

  get_underlying_value (  E::A);
  get_underlying_value (int {});
}
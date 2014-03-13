#include <type_traits>

template<
  typename T,
  typename   = typename std::enable_if<std::is_enum<T>::value>::type,
  typename U = typename std::underlying_type<T>::type
>
U get_underlying_value (T value) {
  return static_cast<U> (value);  
}

int 
main (int argc, char *argv[])
{
  enum class E : int { A, B, C };

  get_underlying_value (  E::A);
  get_underlying_value (int {});
}
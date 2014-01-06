#include <type_traits>

template<
  typename T,
  int(*)[ std::is_enum<T>::value ] = nullptr,
  typename U = typename std::underlying_type<T>::type
>
void func () { }

template<
  typename T, 
  int(*)[ std::is_enum<T>::value == false ] = nullptr,
>
void func () { }

int
main (int argc, char *argv[])
{
  enum E { };

  func<int> ();
  func<E  > ();
}
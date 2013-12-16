#include <type_traits>

template <typename T> struct remove_all_pointers
{ typedef typename std::remove_reference<T>::type type; };
template <typename T> struct remove_all_pointers<T *> :
  remove_all_pointers<typename std::remove_reference<T>::type> {};

template <typename T>
T & dereference(T & p)
{ return p; }

template <typename U>
typename remove_all_pointers<U>::type & dereference(U * p)
{ return dereference(*p); }

#include <iostream>

int main(int argc, char * argv[])
{
  auto x = 42;
  auto p1 = &x;
  auto p2 = &p1;
  auto p3 = &p2;
  std::cout << dereference(p3) << '\n';
}

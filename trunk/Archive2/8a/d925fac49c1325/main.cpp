#include <iostream>
#include <string>
#include <type_traits>
#include <initializer_list>

template <int N>
struct names
{ static char const * value; };
template <int N>
char const * names<N>::value{ "" };

template <int N, typename T>
int constexpr swallow(std::initializer_list<T>)
{ return N; }

template <int N>
int constexpr name(char const (&str)[N])
{ return swallow<N>({ names<N>::value = str }); } /* not constexpr, of course */

template <int N, int Name = 0>
void foo()
{ std::cout << N << " " << names<N>::value << std::endl; }

int main()
{
  foo<22, name("test")>();
}
#include <iostream>

template<class T, class... Ts>
struct foo
{ /* ... */ };

template< class... Ts >
std::ostream& operator<<( std::ostream& os, const foo<Ts...>& )
{
  return os << 42;
}


int main()
{
  std::cout << foo<int>();
}
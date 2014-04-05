#include <iostream>

struct swallow{
  template<typename... Types>
  swallow(Types &&...){}
};

template<int... IS>
int f()
{
  int i = 2;
  swallow{ i = i * IS + IS... };
  return i;
}

int main()
{
  // `i = i * 2 + 2' should be sequenced before `i = i * 3 + 3'
  std::cout << f<2, 3>() << std::endl;
}

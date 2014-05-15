#include <iostream>

template<int... ints>
int add()
{
  int result = 0;
  using expand_variadic_pack  = int[]; // dirty trick, see below
  (void)expand_variadic_pack{0, ((result += ints), void(), 0)... };
  // first void: silence variable unused warning
  // uses braced-init-list initialization rules, which evaluates
  //  the elements inside a braced-init-list IN ORDER, to repetetively
  //  execute a certain operation
  return result;
}

int main()
{
  std::cout << add<1,2,3,4>() << '\n';
}
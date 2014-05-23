#include <iostream>

struct Alice
{
  template <typename A>
  void operator|(const A& /*a*/) const
  {
    std::cout << "operator| member" << std::endl;
  }
};

template <typename A>
void operator|(const A& /*a*/, const Alice& /*alice*/)
{
  std::cout << "operator| non-member" << std::endl;
}

int main()
{
  Alice a;
  Alice b;

  a | b;

  return 0;
}

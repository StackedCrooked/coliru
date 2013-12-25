#include <vector>
#include <functional>
#include <iostream>

int foo(char x)
{
  return -x;
}

struct bar
{
  int n;
  int add(int x)const{return x+n;}
};

int main(void)
{
  using namespace std::placeholders;
  
  std::vector<std::function<int(int)>> v={
    foo,
    [](int x){return 3*x;},
    std::bind(std::plus<int>(),_1,_1),
    std::bind(&bar::add,bar{8},_1),
  };
  for(const auto& f:v)std::cout<<f(5)<<std::endl;
}

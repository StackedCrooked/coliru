#include <algorithm>
#include <iostream>
#include <functional>

struct A
{
  int i;
  A(int i_) : i(i_) {}
  A(A&&) { std::cout << "move!"; i=0; }
  A& operator+=(const int& i_) { i+=i_; return *this; }
  // required for std::plus

  A(const A& a) { i = a.i; }
  A& operator=(const A& a) { i = a.i; return *this; }
};

A operator+(const A& a, const A& b) { return A(a.i+b.i); }

std::ostream& operator<<(std::ostream& os, const A& a)
{
  os << a.i;
  return os;
}
    
int main()
{
  std::vector<A> x = {1, 2, 3};
  auto y = x;
  std::transform(x.begin(), x.end(), x.begin(), std::bind1st(std::plus<A>(), 7));
  for(auto&& item : y) item+=7;
    
  for(auto&& item : x) std::cout << item << '\n';
  for(auto&& item : y) std::cout << item << '\n';
}
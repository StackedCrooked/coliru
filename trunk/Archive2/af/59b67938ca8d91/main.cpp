#include <iostream>
#include <array>

template<int N>
class NumberHolder
{
public:
  NumberHolder();
  int x_;
};

template<int N>
NumberHolder<N>::NumberHolder() : x_(N) {}

template<int N, int M>
void add(NumberHolder<N>& nh)
{
  nh.x_ += M;
}

template<int N, int M>
void mult(NumberHolder<N>& nh)
{
  nh.x_ *= M;
}

template<int N> 
using f_ptr = void(*)(NumberHolder<N>&); 

int main()
{
  NumberHolder<3> nh;

  std::array<f_ptr<3>, 2> operations;
  operations[0] = &add<3, 41>;
  operations[1] = &mult<3, 8>;

  for (int i = 0; i < operations.size(); ++i)
  {
    operations[i](nh); 
  }
  std::cout << nh.x_ << std::endl;
  return 0;
}
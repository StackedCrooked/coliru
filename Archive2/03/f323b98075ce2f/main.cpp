#include <iostream>
using namespace std;

template<int cl, int dim>
struct g_impl
{
  int operator()(int x) { return cl + 1 * x;}    
};

template<int cl>
struct g_impl<cl, 1>
{
  int operator()(int x) { return cl + 3 * x; }    
};

template <int cl, int dim>
class impl_prototype 
:
    public g_impl<cl, dim>
{
public:
  impl_prototype() {}

  int f(int x) { return cl + 2 * g(x); }
  int g(int x) { return g_impl<cl, dim>()(x); }
};

int main ()
{
  impl_prototype<0, 0> test_0;
  impl_prototype<0, 1> test_1;


  cout << test_0.f(5) << " " << test_0.g(5) << std::endl;
  cout << test_1.f(5) << " " << test_1.g(5) << std::endl;


  return 0;
}

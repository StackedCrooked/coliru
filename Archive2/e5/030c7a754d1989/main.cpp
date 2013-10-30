#include <functional>
#include <iostream>

struct F {};
struct G {};

struct Mul {
  template<class X>
  auto operator()(X x, G y)  -> decltype( x * y )
  { return x * y; }
};


auto operator*(F x, G y) -> decltype( std::bind(Mul(), x, y) )
{ return std::bind(Mul(), x, y); }


template<typename> void type_is();

int main()
{
  using namespace std;
  using namespace std::placeholders;

  auto fog = F() * G();
  type_is<decltype(fog()()()()()())>();
}
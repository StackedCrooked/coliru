#include <functional>
#include <iostream>
#include <string> // for "Hello, world!"


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

  auto fog = F() * G(); // странность: bind(Mul(),F(),G()) - мы точно этого хотели?
  type_is<decltype(fog()()()()()())>();
}
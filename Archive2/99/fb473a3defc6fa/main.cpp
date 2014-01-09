#include <functional>
#include <iostream>
#include <string> // for "Hello, world!"

#define JUST_RETURN(...) decltype( __VA_ARGS__ ) { return __VA_ARGS__; }
#define OP(name,op) struct name {                                            \
  template<class X, class Y>auto operator()(X x, Y y) -> JUST_RETURN(x op y) \
};                                                                           \
template<class X, class Y>auto operator op(X x, Y y) -> JUST_RETURN(std::bind(name(), x, y))

OP(Mul, *)
OP(Div, /)
OP(Mod, %)
OP(Add, +)
OP(Sub, -)
OP(EQ, ==)
OP(LT, < )
OP(LE, <=)
OP(GT, > )
OP(GE, >=)

int main()
{
  using namespace std;
  using namespace std::placeholders;

  cout << ( 9 * _1)(5)          << endl;                     // 45
  cout << (_1 *  8)(5)          << endl;                     // 40
  cout << (_1 * _1)(5)          << endl;                     // 25
  cout << (_1 * _2)(5,6)        << endl;                     // 30
  cout << (_1 + _2 * _3)(5,6,7) << endl;                     // 47 (42+5)
  cout << (_3 - _2 * _1)(5,6,7) << endl;                     // -23 (7-30)
  cout << ( 9 * _2)(5,6)        << endl;                     // 54
  cout << (_2+", "+_1+"!")("world",string("Hello")) << endl; // "Hello, world!"
}

    
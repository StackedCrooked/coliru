#include<type_traits>
#include<array>
 
template<class C, class T = int>
using EnableIf = typename std::enable_if<C::value, T>::type;
 
template<unsigned a, unsigned b> struct equal : std::integral_constant<bool, a == b> {};
 
template<unsigned nd, EnableIf<equal<nd,2>>...>
void vector() {}
template<unsigned nd, EnableIf<equal<nd,3>>...>
void vector() {}

int main() {
  static const unsigned num = 3;
  vector<num>();
}
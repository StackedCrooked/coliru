#include<type_traits>

template<unsigned nd, typename std::enable_if<nd == 2>::type...>
void vector() {}
template<unsigned nd, typename std::enable_if<nd == 3>::type...>
void vector() {}

int main() {
  static const unsigned num = 3;
  vector<num>();
}
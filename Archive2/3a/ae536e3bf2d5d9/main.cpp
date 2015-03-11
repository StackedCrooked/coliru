#include <iostream>
#include <type_traits>

int foo();

int main() {
  using F = int();
  std::cout << std::boolalpha
    << "1: " << std::is_same<int(), int(*)()>::value << '\n'
    << "2: " << std::is_same<void(int()), void(int(*)())>::value << '\n'
    << "3: " << std::is_same<F, F*>::value << '\n'
    << "4: " << std::is_same<void(F), void(F*)>::value << '\n'
    << "5: " << std::is_same<void(F), void(F**)>::value << '\n'
    << "6: " << std::is_same<decltype(foo), F>::value << '\n'
    << "7: " << std::is_same<decltype(*foo), F&>::value << '\n'
    << "8: " << std::is_same<decltype(**foo), F&>::value << std::endl;
}

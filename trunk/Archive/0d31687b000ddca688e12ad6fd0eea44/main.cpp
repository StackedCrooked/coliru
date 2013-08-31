#include <iostream>
#include <array>
#include <memory>
#include <type_traits>

struct Data {
  int type : 12;
  int variant : 3;
  bool isTop : 1;

  bool hasFlag(int flag);
 };

int main() {
   std::cout << std::is_pod<Data>::value;
}
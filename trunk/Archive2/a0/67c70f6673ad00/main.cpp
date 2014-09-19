#include <iostream>

struct  Foo {
  union {
    struct {
      int x;
      int y;
      int z;
    };
    struct {
      int array[3];
    };
  };
};

int main() {
  Foo p;
  p.array[0] = 1;
  p.array[1] = 2;
  p.array[2] = 3;
  std::cout << p.x << std::endl;
  std::cout << p.y << std::endl;
  std::cout << p.z << std::endl;
  
}
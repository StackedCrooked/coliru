#include <iostream>

auto add(int a){
  return [=](auto b) {
      return add(a + b);
  };
}

int main()
{
  printf("%d \n", add(7)(1)(1)(2));
}
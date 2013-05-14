#include<iostream>

int f1(int) {
  return 0;
}

char f2(char) {
  return 0;
}

double f3() {
  return 0;
}

int main() {
   std::cout << sizeof(f1) << std::endl;

  return 0;
}
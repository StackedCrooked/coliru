#include <iostream>

int main() {

  int a = 5;
  int b = 6;
  int c[10][2];
  for (int i = 0; i < 10; i++) {
    c[i] = { a, b };
  }

  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 2; j++) {
      std::cout << c[i][j];
    }
  }

  return 0;
}
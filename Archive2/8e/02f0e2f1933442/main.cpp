float halfthree() {
  return 1.5f;
}

float three() {
  return 3.0f;
}

float two() {
  return 2.0f;
}

#include <iostream>
#include <iomanip>
void print(bool b) { std::cout << std::boolalpha << b << '\n'; }

int main() {
  print(halfthree() + halfthree() == three());
  print(halfthree() * two() == three());
  print(halfthree() * two() == halfthree() + halfthree());
  print(two() * halfthree() == three());
  print(two() * halfthree() == halfthree() + halfthree());
}
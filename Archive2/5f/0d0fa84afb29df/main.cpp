#include <cstdint>

using namespace std;

constexpr int64_t ipow(int64_t base, int exp){
  int64_t result = 1;
  while(exp){
    if(exp & 1)
      result *= base;
    exp >>= 1;
    base *= base;
  }
  return result;
}

#include <iostream>

int main() {
    constexpr auto what_is_13_to_the_7th = ipow(13, 7);
    std::cout << what_is_13_to_the_7th << '\n';
}

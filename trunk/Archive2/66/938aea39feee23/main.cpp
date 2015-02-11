#include <iostream>

constexpr int giveMeValue() { return 42; }

struct TryMe {
  static constexpr int arr[1] = {
      giveMeValue()
  };  
};

constexpr int TryMe::arr[1];

int main() {
    int val = TryMe::arr[0];
    std::cout << val;
}

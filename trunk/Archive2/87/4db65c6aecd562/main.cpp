#include <iostream>

int main() {
  #if __has_attribute(__assume_aligned__)
    std::cout << "Test";
  #endif
}

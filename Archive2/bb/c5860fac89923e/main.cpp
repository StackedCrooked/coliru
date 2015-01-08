#include <iostream>

struct AlignedDouble {
  alignas(sizeof(double)) unsigned char_[sizeof(double)];
};

struct UnalignedDouble {
  double _;
};


int main() {
  std::cout << "Aligned double size is: " << sizeof(AlignedDouble) << "\n";
  std::cout << "Unaligned double size is: " << sizeof(UnalignedDouble) << "\n";
  return 0;
}

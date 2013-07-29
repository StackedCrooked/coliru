#include <iostream>

class factorial {
public:
  int operator()(int n) {
    if (n == 0)
      return 1;
    return n * (*this)(n-1);
  }
};

int main()
{
    std::cout << factorial{}(5) << std::endl;
}

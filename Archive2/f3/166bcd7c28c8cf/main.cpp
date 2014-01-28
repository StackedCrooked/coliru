#include <iostream>

class bar {
private:
  static constexpr int foo[] = {1,2,3,4};
public:
  bar () {
    std::cout << sizeof(foo)/sizeof(int) << std::endl;

    print ();
  }

  void print () {
    const int *b = foo;
    std::cout << b[3] << std::endl;
  }
};

constexpr int bar::foo[4];

int main() {
  bar foo;
}

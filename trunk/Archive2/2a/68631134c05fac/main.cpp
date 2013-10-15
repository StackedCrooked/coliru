#include <functional>
#include <memory>
#include <iostream>

struct object {
  int data;
  object(int data) : data(data) {
    std::cout << "object is allocated at " << this << std::endl;
    std::cout << "  x is allocated at" << &this->data << std::endl;
  }
  ~object() { std::cout << "object is destroyed." << std::endl; }
};

std::function<void(int)> counter() {
  object x(0);
  std::cout << "Address of x@counter(): " << &x.data << std::endl;
  std::function<void(int)> increment = [&x](int y) {
    std::cout << "Address of x@increment(): " << &x.data << std::endl;
    x.data += y;
    std::cout << x.data << std::endl;
  };
  return increment;
}

int main() {
  using namespace std;

  auto counter1_increment = counter();
  auto counter2_increment = counter();

  (counter1_increment)(1);
  (counter1_increment)(7);
  (counter2_increment)(1);
  (counter1_increment)(1);
  (counter2_increment)(1);

  return 0;
}
#include <memory>
#include <iostream>

int global_x = 5;

class Foo {
 public:
  ~Foo() {
    std::cout << global_x;
  }
};

void Done(int x) {
  global_x = 6;
}

int Process(std::unique_ptr<Foo> foo) {
  return 5;
}

int main() {
  Done(Process(std::unique_ptr<Foo>(new Foo())));
}

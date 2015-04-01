#include <iostream>

struct Base {
  Base() = default;
  Base(const Base&) = default;
  Base(Base&&) {std::cout << "move\n";}
};

struct Derived : Base {
};

int main() {
  const Base& b = true ? Derived() : Base();
}
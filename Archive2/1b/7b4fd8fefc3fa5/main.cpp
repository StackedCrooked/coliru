#include <array>

struct A {
    std::array<int,3> arr = {{1,2,3}};
};

int main() {
  const A a;
}
#include <utility>

struct MyClass {
  MyClass& operator = (const MyClass& other) & = default;
  MyClass& operator = (MyClass&& other) & = default;
};

int main() {
    MyClass m;
    m = m;
    m = std::move(m);
    std::move(m) = m;
}

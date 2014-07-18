#include <mutex>
#include <iostream>
#include <vector>
#include <utility>

class Foo {
  int data = 42;
  mutable std::mutex mtx;
    
  template <typename Other>
  Foo(Other&& other, std::lock_guard<std::mutex>&&) :
    data(std::forward<Other>(other).data) {}

  template <typename Other>
  void assign(Other&& other) {
    std::unique_lock<std::mutex> my_lock(mtx, std::defer_lock);
    std::unique_lock<std::mutex> other_lock(other.mtx, std::defer_lock);
    std::lock(my_lock, other_lock);
    data = std::forward<Other>(other).data;
  }

public:
  Foo() = default;
  Foo(int value) : data(value) {}
  Foo(Foo const& other) :
    Foo(other, std::lock_guard<std::mutex>(other.mtx)) {}
  Foo(Foo&& other) :
    Foo(std::move(other), std::lock_guard<std::mutex>(other.mtx)) {}

  Foo& operator = (Foo const& other) & {
    assign(other);
    return *this;
  }

  Foo& operator = (Foo&& other) & {
    assign(std::move(other));
    return *this;
  }
  
  friend std::ostream& operator << (std::ostream& os, Foo const& f) {
    std::lock_guard<std::mutex> guard(f.mtx);
    os << f.data;
    return os;
  }
};

int main() {
  Foo a(42);
  std::cout << a << '\n';
  Foo b = a; // Copy construction
  std::cout << b << '\n';
  Foo c = std::move(a); // Move construction
  std::cout << c << '\n';
  a = c; // Copy assignment
  std::cout << a << '\n';
  a = std::move(c); // Move assignment
  std::cout << a << '\n';

  std::vector<Foo> vec = {1,2,3};
  for (auto const& i : vec) {
      std::cout << i << '\n';
  }
  auto vec2 = vec;
  for (auto const& i : vec2) {
      std::cout << i << '\n';
  }
}

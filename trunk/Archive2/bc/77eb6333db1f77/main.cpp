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

class Bar : public Foo {
  int data = 11;
  mutable std::mutex mtx;
    
  template <typename Other>
  Bar(Other&& other, std::lock_guard<std::mutex>&&) :
    Foo(std::forward<Other>(other)),
    data(std::forward<Other>(other).data) {}

  template <typename Other>
  void assign(Other&& other) {
    std::unique_lock<std::mutex> my_lock(mtx, std::defer_lock);
    std::unique_lock<std::mutex> other_lock(other.mtx, std::defer_lock);
    std::lock(my_lock, other_lock);
    static_cast<Foo&>(*this) = std::forward<Other>(other);
    data = std::forward<Other>(other).data;
  }

public:
  Bar() = default;
  Bar(int x, int y) : Foo(x), data(y) {}
  Bar(Bar const& other) :
    Bar(other, std::lock_guard<std::mutex>(other.mtx)) {}
  Bar(Bar&& other) :
    Bar(std::move(other), std::lock_guard<std::mutex>(other.mtx)) {}

  Bar& operator = (Bar const& other) & {
    assign(other);
    return *this;
  }

  Bar& operator = (Bar&& other) & {
    assign(std::move(other));
    return *this;
  }

  friend std::ostream& operator << (std::ostream& os, Bar const& f) {
    std::lock_guard<std::mutex> guard(f.mtx);
    os << '(' << static_cast<Foo const&>(f) << ", " << f.data << ')';
    return os;
  }
};


int main() {
  Bar a(42, 13);
  std::cout << a << '\n';
  auto b = a; // Copy construction
  std::cout << b << '\n';
  auto c = std::move(a); // Move construction
  std::cout << c << '\n';
  a = c; // Copy assignment
  std::cout << a << '\n';
  a = std::move(c); // Move assignment
  std::cout << a << '\n';

  Foo f = a;
  std::cout << f << '\n';

  std::vector<Bar> vec = {{1,2}, {3,4}};
  for (auto const& i : vec) {
      std::cout << i << '\n';
  }
  auto vec2 = vec;
  for (auto const& i : vec2) {
      std::cout << i << '\n';
  }
}

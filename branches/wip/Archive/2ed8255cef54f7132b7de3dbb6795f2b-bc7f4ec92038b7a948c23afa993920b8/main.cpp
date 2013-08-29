#include <memory>
#include <utility>

struct placement_deleter {
  template <typename T>
  void operator() (T* p) { p->~T(); }
};

template <typename T>
struct alignas(T) SpaceFor {
  char c[sizeof(T)];
};

template <typename T>
using PlacementPtr = std::unique_ptr<T,placement_deleter>;

template <typename T, typename Space, typename... Args>
PlacementPtr<T> placement_unique(Space& space, Args&&... args) {
  static_assert(sizeof(Space) >= sizeof(T), "Not enough space.");
  static_assert(alignof(Space) >= alignof(T), "Space not properly aligned.");
  return PlacementPtr<T>(new (&space) T(std::forward<Args>(args)...));
}

#include <iostream>

class MyClass {
  int val_;
public:
  MyClass() : val_(-1) {
    std::cout << "MyClass()\n";
  }
  ~MyClass() {
    std::cout << "~MyClass(" << val_ << ")\n";
  }

  MyClass(int a) : val_(a) {
    std::cout << "MyClass(" << a << ")\n";
  }

  MyClass(const std::string& a) : val_(-1) {
    std::cout << "MyClass(\"" << a << "\")\n";
  }

  void doStuff() {
    std::cout << "doStuff()\n";
  }
};

int main(int argc, char*[]) {
  SpaceFor<MyClass> mem[2];
  PlacementPtr<MyClass> p;
  if (argc > 1)
    p = placement_unique<MyClass>(mem, 1);
  else
    p = placement_unique<MyClass>(mem, "string");
  p->doStuff();
  auto q = placement_unique<MyClass>(mem[1], 42);
  std::cout << sizeof(MyClass) << ' ' << sizeof(mem) << ' ' << &mem << ' ' << p.get() << ' ' << q.get() << '\n';

  // In C++1y:
  // std::optional<MyClass> c;
  // if (something)
  //   c.emplace(1);
  // else
  //   c.emplace("string");
  // c->doStuff();
}

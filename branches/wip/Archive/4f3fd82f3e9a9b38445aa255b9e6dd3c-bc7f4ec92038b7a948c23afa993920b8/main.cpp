#include <memory>

struct placement_deleter {
  template <typename T>
  void operator() (T* p) { p->~T(); }
};

template <typename T>
using SpaceFor = char[sizeof(T)] alignas(T);
template <typename T>
using PlacementPtr = std::unique_ptr<T,placement_deleter>;

template <typename T, typename Space, typename... Args>
PlacementPtr<T> placement_unique(Space& space, Args&&... args) {
  static_assert(sizeof(Space) >= sizeof(T), "Not enough space.");
  static_assert(alignof(Space) >= alignof(T), "Space not properly aligned.");
  T* p = new (&space) T(std::forward<Args>(args)...);
  return PlacementPtr<T>(p);
}

#include <iostream>

class MyClass {
public:
  MyClass() {
    std::cout << "MyClass()" << std::endl;
  }
  ~MyClass() {
    std::cout << "~MyClass()" << std::endl;
  }

  MyClass(int a) {
    std::cout << "MyClass(" << a << ")" << std::endl;
  }

  MyClass(const std::string& a) {
    std::cout << "MyClass(\"" << a << "\")" << std::endl;
  }

  void doStuff() {
    std::cout << "doStuff()" << std::endl;
  }
};

int main(int argc, char*[]) {
  SpaceFor<MyClass> mem;
  PlacementPtr<MyClass> p;
  if (argc > 1)
    p = placement_unique<MyClass>(mem, 1);
  else
    p = placement_unique<MyClass>(mem, "string");
  p->doStuff();

  // In C++1y:
  // std::optional<MyClass> c;
  // if (something)
  //   c.emplace(1);
  // else
  //   c.emplace("string");
  // c->doStuff();
}

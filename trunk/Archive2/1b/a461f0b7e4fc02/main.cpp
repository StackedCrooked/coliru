#include <type_traits>

template <typename Class>
class RBObject {
  static_assert(Class::IsClassData, "Isn't a ClassData, and that's bad");
};

template <typename Ty>
struct ClassData {
  static const bool IsClassData = true;
};

class Foo {};

using FooClass = ClassData<Foo>;

void f() {
  RBObject<FooClass> F;
  (void)F; // Silence warning
  
  RBObject<int> ShouldNotCompile;
  RBObject<Foo> AlsoShouldNotCompile;
}

int main() {
  f();
}
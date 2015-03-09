template <typename Ty>
class ClassData {};

class Foo {};

using FooClass = ClassData<Foo>;

template <typename Class>
class RBObject {};

void f() {
  RBObject<FooClass> F;
  (void)F; // Silence warning
}

int main() {
  f();
}
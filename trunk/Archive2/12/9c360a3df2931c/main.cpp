struct Foo {
  virtual int f() = 0;
};
struct FooImpl final : Foo {
  virtual int f() override { return 42; }
};

#include <memory>
int main() {
  std::unique_ptr<Foo, void(*)(Foo*)> ptr(new FooImpl, [](Foo* p){delete static_cast<FooImpl*>(p);});
  return ptr->f();
}
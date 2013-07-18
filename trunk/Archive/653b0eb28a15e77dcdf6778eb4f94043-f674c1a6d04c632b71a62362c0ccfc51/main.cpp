namespace foo {
  namespace foo {
    typedef int Foo;
  }
  struct Foo {
    int x;
    Foo( foo::Foo const& o ):x(o.x) {}
  };
}

int main() {
  ::foo::Foo foo_(::foo::foo::Foo{});
}

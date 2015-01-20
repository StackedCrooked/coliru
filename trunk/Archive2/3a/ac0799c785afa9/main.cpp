struct B{};

void bar(int, B){} // second overload

struct A{
  void foo()
  {
    bar(2, B{});
  }

  void bar(int){} // first overload
};

int main() {
  A a;
  a.foo();
}
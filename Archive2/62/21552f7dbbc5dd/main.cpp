constexpr int foo(int&& x) { return x; }

int main() {
  static constexpr int&& i = 42;
  constexpr int x = foo(42);

  return 0;
}
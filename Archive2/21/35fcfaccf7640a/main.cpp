extern const int x;

struct A {
  constexpr A () {}
  const int y { x };
};

const int x = 123;

int main() {
  constexpr A a;
}

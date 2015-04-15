struct Base1 {
  void operator()(int) {}
};

struct Base2 {
  void operator()(double) {}
};

struct Derived : Base1, Base2 {};

int main() {
  Derived d;
  d(0);
  d(0.0);
}

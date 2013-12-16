class Foo {
  double value_;
 public:
  explicit Foo(double value) { value_ = value; }
  operator double() const { return value_; }
  Foo operator+(const Foo& other) { return Foo(value_ + other.value_); }
};

int main() {
    Foo foo1(1);
    Foo foo2(2);
    Foo result = foo1 + foo2;
}
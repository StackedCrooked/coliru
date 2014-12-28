struct A {
  virtual void f()=0; // abstract
};

struct Ad : A {
  virtual void f() {} // not abstract
};

struct B {
  operator Ad () const { return Ad(); }
};

void test(A const &lhs) {}

int main()
{
 B b;
 test(b);
}
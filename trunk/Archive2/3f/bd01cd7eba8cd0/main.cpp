class base {
  int a_;
public:
  base(int x)
  : a_(x) {}
  
  base(base const& cpy)
  : a_(cpy.a_) {}
};

class A : public base {
public:
  using base::base;
};

class B : public base  {
public:
  using base::base;
};

int main() {
    A a(123);
    B b(a);
  
  return 0;
}
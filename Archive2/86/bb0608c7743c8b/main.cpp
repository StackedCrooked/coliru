class foo {
 public:
  foo(int x) : x_(x) {}
  int get() {
    return x_;
  }
 private:
  int x_;
};

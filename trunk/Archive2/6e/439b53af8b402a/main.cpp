//typedef void __attribute__((const)) Cb();

void __attribute__((pure)) cb();

int foo(int const& a) {
  int x = a;
  cb();
  return x - a;
}
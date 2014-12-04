typedef void (*Cb)() __attribute__((const));

int foo(int const& a, Cb cb) {
  int x = a;
  cb();
  return x - a;
}
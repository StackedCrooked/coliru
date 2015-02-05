struct Broken {
  Broken() : b(1), a(b + 1) {}
  int a;
  int b;
};
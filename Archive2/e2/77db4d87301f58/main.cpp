class A {
  void f() {
    a = 0;
    return;
  }

  void g() {
    a = 1;
    int b = a;
    f();
    int c = b;
  }

  int a;
}
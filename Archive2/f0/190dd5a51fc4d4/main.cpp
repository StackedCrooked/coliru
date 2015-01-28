using ref = char&;

ref foo(ref x) {
  return ref{x};
}

int main() {
  char a;
  foo(a);
  return 0;
}
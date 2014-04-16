void f(int &&x) {
  x = 5;  // Which memory does this assignment apply to?
}

int main() {
  int i;
  f(i);
  // At this point, where is the value of 5?
  return 0;
}
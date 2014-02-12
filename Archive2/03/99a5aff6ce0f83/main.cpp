template <int D, typename T>
void Foo(T x[D]) {
  // details omitted
}

int main() {
  float x[3];
  Foo(x);  // C2784: could not deduce template argument for 'T [D]' from 'float [3]'
  return 0;
}
template<class T>
struct A {
  typedef int foo;
};

template<class T>
typename A<T>::foo func (T) {
  return 0;
}

template<>
struct A<int> {
  static int const foo = 0;
};

int main () {
  func (1.2f); // legal
  func (1234); // ill-formed
}
template<class T, bool(*fptr)(T)>
struct A {
  bool operator ()(T val) const {
    return fptr (val);
  }
};

template<class T>
bool cond (T) {
  static_assert (T {}, "!!");
  return {};
}

template<class T, bool(*c)(T) = cond>
A<T, c> func (T val) {
  return {};
}

int main() {
  auto x = func (123);
  
  /* comment out to make clang++ static_assert
   *
   * x (123);
  */
}
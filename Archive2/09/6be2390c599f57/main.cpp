template <typename Fn>
auto foo(Fn F) {
  return F();
}

int main () {
  int j = 12;
  
  auto fn = [&j]() {
    auto inner = [&j]() {};
    return inner;
  };
  auto InnerFromCopy = foo(fn);
  InnerFromCopy();
}
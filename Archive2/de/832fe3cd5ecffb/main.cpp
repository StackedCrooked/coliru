class test {

  // recursively template 
  template<typename T, typename... R>
  void add(T /*t*/, R... r) {
    // do something with the rest
    if(sizeof...(r))
      add(r...);
  }
  // since the variadic template add is recursive, there have to be an end.
  void add() {}

public:

  template<typename... T>
  explicit test(T... rest) {
    add(rest...);
  }
};

int main() {
  test t1(1);
  test t2(1, 2);
  test t3(1, 2, 3);
}

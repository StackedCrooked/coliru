struct X {
    int operator++(int) const { return 0; }
};

// the following two function declarations are equivalent
auto incr(auto x) { return x++; }

template <typename T>
auto incr2(T x) { return x++; }

int main()
  {
      incr(X());
      incr2(X());
  }
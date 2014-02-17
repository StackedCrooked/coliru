struct Z {
  static constexpr unsigned int n = 0;

  template<typename T>
  using replace = T;
};

template<typename T>
struct S {
  static constexpr unsigned int n = T::n + 1;

  template<typename U>
  // using replace = T::replace<U>;
  using replace = typename T::template replace<U>;
};


#include <iostream>

int main()
{
    std::cout << S<S<Z>>::n;
}
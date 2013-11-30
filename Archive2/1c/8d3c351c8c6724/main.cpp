template<class F>
struct A{
  template<int N>
  struct B{
    using type = int;
  };
};

template<class F, int N >
using alias_A = typename A<F>::B<N>::type;

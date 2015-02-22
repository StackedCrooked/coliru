template<bool V> struct answer { answer(int) {} bool operator()(){return V;}};

template<bool no, bool yes, int f, int p> struct IsPrimeHelper
  : IsPrimeHelper<p % f == 0, f * f >= p, f + 2, p> {};
template<bool yes, int f, int p> struct IsPrimeHelper<true, yes, f, p> { using type = answer<false>; };
template<int f, int p> struct IsPrimeHelper<false, true, f, p> { using type = answer<true>; };

template<int I> using IsPrime = typename IsPrimeHelper<!(I&1), false, 3, I>::type;
template<int I>
struct X { static const int i = I; int a[i]; }; 

template<typename A> struct foo;
template<>struct foo<answer<true>>{
  template<int I> using typen = X<I>;
};
template<> struct foo<answer<false>>{
  static const int typen = 0;
};

int constexpr g() {
    return 234799;
}

int main() {
  auto b = foo<IsPrime<g()>>::typen<1>(); // Syntax error if not prime
  return 0;
}
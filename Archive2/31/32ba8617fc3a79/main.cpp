#define requires(...)
#define Domain(T) typename DomainT<T>::type

template <typename T1, typename T2>
struct pair {
  pair(T1 f, T2 s) : first(f), second(s) {}
  T1 first;
  T2 second;
};

struct mult_t {
  int operator()(int a, int b) { return a * b; }
};

#include <type_traits>

template <typename T, typename = void>
struct DomainT {
  typedef void type;
};
template<typename T >
struct DomainT<T, typename std::enable_if< std::is_class<T>{} >::type> {
  template<typename>
  struct deduce;
  
  template<typename R, typename C, typename... Args>
  struct deduce<R (C::*)(Args...)>
  {
      using type = typename std::common_type<Args...>::type;
  };
  
  using type = typename deduce< decltype(&T::operator()) >::type;
};
// for each function in your program, specialize this struct
//template <>
//struct DomainT<mult_t> { typedef int type; };

template <typename Op>
requires(BinaryOperation(Op))
Domain(Op) square(const Domain(Op)& x, Op op) {
  return op(x,x);
}

#include <iostream>

int main() {
  mult_t mult;
  std::cout << square(4, mult) << "\n";
  return 0;
}
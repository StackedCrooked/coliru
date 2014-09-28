#include <iostream>
#include <typeinfo>

template<typename T, typename... Ts>
struct LastTypeOfTs {
   typedef typename LastTypeOfTs<Ts...>::type type;
};

template<typename T>
struct LastTypeOfTs<T> {
  typedef T type;
};

template<typename... Ts>
typename LastTypeOfTs<Ts...>::type f() {
  std::cout << typeid(typename LastTypeOfTs<Ts...>::type).name() << std::endl;
  return typename LastTypeOfTs<Ts...>::type();
}

int main() {
    
  f<int, double, int, float>();
}
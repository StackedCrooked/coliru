#include <functional>
#include <iostream>

template <typename T, typename ...Args>
T construct(Args... args) {
 return T(args...);   
}

template <class T, class Head>
T random_class_impl(std::function<T(Head)> f) {
  // Generate a random head
  Head head{};
  std::function<T()> fun = [&head, f](){ return f(head); };
  return fun();
}

template <class T, class Head, class... Tail>
T random_class_impl(std::function<T(Head, Tail...)> f)  {
  // Generate a random head
  Head head{};
  std::function<T(Tail...)> fun = [&head, f](Tail... args){ return f(head, args...); };
  return random_class_impl<T, Tail...>(fun);  
}

template <class T, class... Args>
T random_class() {
  // Randomly generate a variable of type head
  std::function<T(Args...)> c = &construct<T, Args...>;
  return random_class_impl<T, Args...>(c);
}

struct A {
  int i;
  double d;
  A(int ii, double dd) : i{ii}, d{dd} {}
  std::string print() {
    return std::to_string(i) + " " + std::to_string(d);
  }
};

int main() {
  auto my_a = random_class<A, int, double>();
  std::cout << my_a.print() << std::endl;
}
#include <iostream>
#include <functional>
#include <type_traits>

template<typename T>
struct is_callable_impl {
 private:
  typedef char(&yes)[1];
  typedef char(&no)[2];
    
  struct fallback {
    void operator()();
  };
  struct derived
    : T, fallback {};
    
  template<typename U, U> struct check;
    
  template<typename>
  static yes test(...);
    
  template<typename C>
  static no test(check<void (fallback::*)(), &C::operator()>*);
    
 public:
   static constexpr bool value = sizeof(test<derived>(0)) == sizeof(yes);
};

template<typename T>
struct is_callable
: std::conditional<
    std::is_function<T>::value,
    std::true_type,
    typename std::conditional<
        std::is_class<T>::value,
        is_callable_impl<T>,
        std::false_type
    >::type
>::type {};

class Nope {};

class Base {
  void operator()() {};
};

class Final final {
  void operator()() {};
};

class Overload {
  void operator()() {};
  void operator()(const int) {};
};

class Template {
  template<typename T>
  void operator()(const T) {};
};

static void foo() {}

int main() {
  const auto lambda1 = [](){};
  const auto lambda2 = [](const int){};
  const auto lambda3 = [](){
    return true;
  };
  const auto bind = std::bind(lambda2, 4);
  std::cout << std::boolalpha 
            << "bool:     " << is_callable<bool>::value << '\n'
            << "int:      " << is_callable<int>::value << '\n'
            << "foo:      " << is_callable<decltype(foo)>::value << '\n'
            << "lambda1:  " << is_callable<decltype(lambda1)>::value << '\n'
            << "lambda2:  " << is_callable<decltype(lambda2)>::value << '\n'
            << "lambda3:  " << is_callable<decltype(lambda3)>::value << '\n'
            << "bind:     " << is_callable<decltype(bind)>::value << '\n'
            << "Nope:     " << is_callable<Nope>::value << '\n'
            << "Base:     " << is_callable<Base>::value << '\n'
            << "Template: " << is_callable<Template>::value << '\n'
//            << "Final:    " << is_callable<Final>::value << '\n'  // Need this one to work!
            << "Overload: " << is_callable<Overload>::value << std::endl;
}
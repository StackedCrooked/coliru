#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <functional>

template<class T>
T convert(const std::string& str) {
  std::stringstream ss(str);
  T res;
  ss >> res;
  return res;
}

template <int I, int N, class R, class... Args>
struct Expander {
  template<class... Expanded>
  static void expand(std::function<R(Args...)>& func,
                     const std::vector<std::string>& args,
                     const Expanded&... expanded) {
    Expander<I+1, N, R, Args...>::expand(func, args, expanded..., args[I]);
  }
};

template <int I, class R, class... Args>
struct Expander<I, I, R, Args...> {
  template<class... Expanded>
  static void expand(const std::function<R(Args...)>& func,
                     const std::vector<std::string>& args,
                     const Expanded&... expanded) {
    func(convert<Args>(expanded)...);
  }
};


template <typename ReturnType, typename... ArgumentTypes>
class FunctionGear {
 public:
  FunctionGear(std::function<ReturnType(ArgumentTypes...)> func)
   : mNativeFunction(func) {
  }

  void Invoke(const std::vector<std::string>& args) {
    Expander<0, sizeof...(ArgumentTypes), ReturnType, ArgumentTypes...>::expand(mNativeFunction, args);
  }

 private:

  std::function<ReturnType(ArgumentTypes...)> mNativeFunction;
};

void foo(int x, float y) {
  std::cout << "foo(" << x << ", " << y << ")\n";
}

int main() {
  FunctionGear<void, int, float> fg(&foo);
  fg.Invoke({"123", "1.5"});
}

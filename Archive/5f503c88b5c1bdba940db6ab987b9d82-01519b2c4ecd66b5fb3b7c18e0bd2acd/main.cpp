#include <functional>
#include <utility>
#include <vector>

class Store
{
  std::vector<std::function<void()>> funcs;

public:
  template<typename F, typename... Args>
  void registerfunc(const F& f, const Args&... args)
  {
    funcs.push_back([f,args...]{f(args...);});
  }

  void call() const {
    for(auto&& f : funcs)
      f();
  }
};

#include <cstdarg>
#include <iostream>

template <typename T>
void print(const T& t) {
    std::cout << t << std::endl;
}

extern "C" void print_int_varags(int first, ...) {
    if (!first) return;
    std::cout << '{';
    va_list ap;
    va_start(ap, first);
    while(first) {
        std::cout << ' ' << first;
        first = va_arg(ap, int);
    }
    va_end(ap);
    std::cout << " }" << std::endl;
}

int main() {
    Store store;
    store.registerfunc(&print<int>, 42);
    store.registerfunc(&print<unsigned long long>, 1ULL << 40);
    store.registerfunc(&print_int_varags, 1, 2, 3, 4, 5, 6, 0);

    store.call();
}

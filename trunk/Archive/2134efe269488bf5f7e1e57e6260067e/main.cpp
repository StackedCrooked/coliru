#include <tuple>
#include <memory>

#define MAKE_UNIQUE(TEMPLATE_LIST, PADDING_LIST, LIST, COMMA, X1, X2, X3, X4) \
  template<class T COMMA LIST(_CLASS_TYPE)> \
  std::unique_ptr<T> make_unique(LIST(_TYPE_REFREF_ARG)){ \
    return std::unique_ptr<T>(new T(LIST(_FORWARD_ARG))); \
  }


_VARIADIC_EXPAND_0X(MAKE_UNIQUE, , , , )
#undef MAKE_UNIQUE

int main(){
  auto u1 = make_unique<int>();
  auto u2 = make_unique<int>(5);
  auto u3 = make_unique<std::tuple<int, int>>(42, 1729);
}
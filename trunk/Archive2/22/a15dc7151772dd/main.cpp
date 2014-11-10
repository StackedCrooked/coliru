#include <iostream>
#include <utility>

namespace details {
  struct magic {
    template<class U> friend
    auto operator, (U&& val, magic) -> decltype (std::forward<U>(val)) {
      return std::forward<U> (val);
    }
  };
}

namespace {
  details::magic _;
}

void g () { return  ; }
int  h () { return 0; }

template<class T>
void f (T const&) {
  std::cerr << __PRETTY_FUNCTION__ << "\n";
}

int main () {
  f ((g (), _));
  f ((h (), _));
}
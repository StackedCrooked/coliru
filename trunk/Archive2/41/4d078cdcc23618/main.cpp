#include <functional>

namespace std {
  template<class E>class hash {
    using sfinae = typename std::enable_if<std::is_enum<E>::value, E>::type;
  public:
    size_t operator()(const E&e) const {
      return std::hash<typename std::underlying_type<E>::type>()(e);
    }
  };
}

enum foo { BAR, BAZ };
class quux {};

int main() {
  // Compiles.
  std::hash<foo>foo_hash;
  // Gives a compile-time error: no type named ‘type’ in ‘struct
  // std::enable_if<false, quux>’.
  std::hash<quux>quux_hash;
  return 0;
}
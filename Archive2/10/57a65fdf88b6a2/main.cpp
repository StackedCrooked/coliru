#include <cassert>
#include <tuple>
#include <type_traits>
#include <vector>

template<typename ... Ts>
class A {
public:
  // "Simple" method. Does not perfect forward.
  // Caller's expressions are copied/moved/converted at the callsite
  // into Ts, and then moved (for non-reference types) or copied
  // (reference types) into the vector.
  void simple_method(Ts... ts) {
    // some code 
    std::vector<std::tuple<Ts...>> vec;
    vec.emplace_back(std::forward<Ts>(ts)...);
    // some other code
  }

  // "Perfect forwarding" method.
  // Caller's expressions are perfectly forwarded into the vector via
  // emplace.
  template <typename...Us>
  void perfect_forwarding_method(Us&&...us) {
    // some code 
    std::vector<std::tuple<Ts...>> vec;
    vec.emplace_back(std::forward<Us>(us)...);
    // some other code
  }

  // Constraint alias.
  template <typename...Us>
  using Constructible = typename std::enable_if<
    std::is_constructible<std::tuple<Ts...>, Us...>::value
  >::type;

  // "Constrained Perfect forwarding" method.
  // Caller's expressions are perfectly forwarded into the vector via
  // emplace. Substitution failure of tuple<Ts...> cannot be constructed
  // from std::forward<Us>(us)...
  template <typename...Us, typename = Constructible<Us...>>
  void constrained_perfect_forwarding_method(Us&&...us) {
    // some code 
    std::vector<std::tuple<Ts...>> vec;
    vec.emplace_back(std::forward<Us>(us)...);
    // some other code
  }
};

int main() {
  {
    int x = 42;
    A<std::string, double, int&> a;
    a.simple_method("hello, world!", 3.14f, x);
    a.perfect_forwarding_method("hello, world!", 3.14f, x);
    a.constrained_perfect_forwarding_method("hello, world!", 3.14f, x);
  }
  {
    int x = 42;
    A<int&&, int&&> a;
    a.simple_method(42, std::move(x));
    a.perfect_forwarding_method(std::move(x), 13);
    a.constrained_perfect_forwarding_method(std::move(x), 13);
  }
}

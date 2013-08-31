#include <array>
#include <cstddef>
#include <iostream>
#include <type_traits>

template <int... I> struct indices {};
template <int N, int... I> struct make_indices :
  make_indices<N-1,N-1,I...> {};
template <int... I> struct make_indices<0,I...> : indices<I...> {};

class Node
{
  unsigned _i;
public:
  // make noncopyable
  Node(const Node& ref) = delete;      
  Node& operator=(const Node& ref) = delete;

  // but moveable
  Node(Node&& ref) = default;
  Node& operator=(Node&& ref) = default;

  // we do not have a default construction
  Node(unsigned i): _i(i) {}

  friend std::ostream& operator << (std::ostream& os, const Node& node) {
    return os << node._i;
  }
};

template <int... I>
inline std::array<Node, sizeof...(I)> array_maker(indices<I...>) {
  return std::array<Node, sizeof...(I)>{ (I+1)... };
}

template <std::size_t N>
inline std::array<Node, N> array_maker() {
  return array_maker(make_indices<N>());
}

template <typename T, std::size_t N>
std::ostream& operator << (std::ostream& os, const std::array<T, N>& array) {
    os << "{ ";
    bool first = true;
    for (auto& i : array) {
        if (first)
            first = false;
        else
            os << ", ";
        os << i;
    }
    os << " }";
    return os;
}

int main() {
    auto a = array_maker<5>();
    static_assert(std::is_same<decltype(a),std::array<Node, 5>>::value, "Test failure.");
    std::cout << a << std::endl;
}

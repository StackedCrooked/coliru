#include <array>
#include <cstddef>
#include <iostream>
#include <type_traits>

template <int... I> struct indices {};
template <int N, int... I> struct make_indices :
  make_indices<N-1,N-1,I...> {};
template <int... I> struct make_indices<0,I...> : indices<I...> {};

template <typename T, typename F, int... I>
inline std::array<T, sizeof...(I)> array_maker(F&& f, indices<I...>) {
  return std::array<T, sizeof...(I)>{ std::forward<F>(f)(I)... };
}

template <typename T, std::size_t N, typename F>
inline std::array<T, N> array_maker(F&& f) {
  return array_maker<T>(std::forward<F>(f), make_indices<N>());
}

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

template<unsigned count>
class ParentNode
{
  std::array<Node,count> _children;
public:
  ParentNode() 
     : _children(array_maker<Node, count>([](unsigned i){return i+1;}))
  {}
  
  friend std::ostream& operator << (std::ostream& os, const ParentNode& pn) {
    return os << pn._children;
  }
};

int main() {
    ParentNode<5> pnode = {};
    std::cout << pnode << std::endl;
}

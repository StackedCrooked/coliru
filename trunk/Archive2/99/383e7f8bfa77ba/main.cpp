#include <cstddef>

namespace detail {
    template<std::size_t N>
    class Graph {
    public:
        class Node {
            
        };

        void addNode(Node) { }
    };
}

#define Graph ::detail::Graph<__COUNTER__>

int main() {
    Graph a;
    Graph b;

    auto node = decltype(a)::Node();
    a.addNode(node); // ok
    b.addNode(node); // type error

    return 0;
}

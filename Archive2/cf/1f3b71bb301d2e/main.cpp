#include <array>
#include <boost/optional.hpp>

namespace Tree {

    using boost::optional;

    template <typename LeafValue, int level> struct Node;

    template <typename LeafValue> struct Node<LeafValue, 3> {
        LeafValue value;
    };

    template <typename LeafValue, int level> struct Node {
        std::array<optional<Node<LeafValue, level+1> >, 4> children;
    };

    template <typename LeafValue> using Root = Node<LeafValue, 0>;
}


int main() 
{
    Tree::Root<int> a = {
    };
}

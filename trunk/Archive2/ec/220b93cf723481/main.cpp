#include <iostream>
#include <boost/variant.hpp>
#include <vector>

struct NodeInfo { 
    int id; 
};

using Tree = boost::make_recursive_variant<
        NodeInfo,
        std::vector<boost::recursive_variant_>
    >::type;

// for nicer code:
using Branch = std::vector<Tree>;
using Leaf   = NodeInfo; 

static std::ostream& operator<<(std::ostream& os, Leaf const& ni) { return os << ni.id; }
static std::ostream& operator<<(std::ostream& os, Branch const& b) { 
    os << "{ ";
    for (auto& child: b) os << child << " ";
    return os << "}";  
}

int main()
{
    Tree tree = Branch { Leaf { 1 }, Leaf { 2 }, Leaf { 3 } };
    boost::get<Branch>(tree).push_back(tree);
    std::cout << tree << "\n";
}

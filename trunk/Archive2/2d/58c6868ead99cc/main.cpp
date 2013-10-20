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
    auto branch1 = Branch { 
        Leaf { 2 }, 
        Leaf { 1 }, 
        Branch { 
            Leaf { 42 }, 
            Leaf { -42 }, 
        }
    };

    Tree tree = Branch { branch1, Leaf { 0 }, branch1 };

    std::cout << tree << "\n";
}

#include <iostream>
#include <boost/variant.hpp>
#include <vector>

struct NodeInfo { 
    int id; 
};

typedef boost::make_recursive_variant<
        NodeInfo,
        std::vector<boost::recursive_variant_>
    >::type Tree;

// for nicer code:
typedef std::vector<Tree> Branch;
typedef NodeInfo Leaf; 

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

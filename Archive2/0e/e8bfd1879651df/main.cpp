#include <iostream>
#include <boost/variant.hpp>
#include <vector>

struct NodeInfo {
    NodeInfo(int id) : id(id) {}
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
    for (Branch::const_iterator it = b.begin(); it!= b.end(); ++it) 
        os << *it  << " ";
    return os << "}";  
}

int main()
{
    Branch branch1;
    branch1.push_back(2);
    branch1.push_back(1);
    
    Branch subbranch;
    subbranch.push_back(42);
    subbranch.push_back(-42);
    
    branch1.push_back(subbranch);

    Branch rootbranch;
    rootbranch.push_back(branch1);
    rootbranch.push_back(0);
    rootbranch.push_back(branch1);

    Tree tree = rootbranch;

    std::cout << tree << "\n";
}

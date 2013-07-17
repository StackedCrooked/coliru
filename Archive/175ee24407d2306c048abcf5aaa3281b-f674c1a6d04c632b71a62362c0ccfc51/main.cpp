#include <string>
#include <vector>
#include <boost/unordered_map.hpp>
#include <unordered_set>
#include <map>
#include <set>

template <typename T>
class tree {
    struct node {
        T value;
        std::set<node> children;
    };
    
    node root;
};

template <typename TK, typename TV>
class unordered_tree {
    struct node {
        TV value;
        boost::unordered_map<TK, node> children;
    };
    
    node root;
};

int main() {
    tree<int> arf; // Works
    unordered_tree<char, int> kaboom; // OH GOD
    
}
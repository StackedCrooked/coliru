#include <string>
#include <vector>
#include <unordered_map>
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

template <typename TK, typename TK>
class unordered_tree {
    struct node {
        TV value;
        std::unordered_map<TK, node> children;
    };
    
    node root;
};

int main() {
    tree<int> arf; // Works
    unordered_tree<int> kaboom; // OH GOD
    
}
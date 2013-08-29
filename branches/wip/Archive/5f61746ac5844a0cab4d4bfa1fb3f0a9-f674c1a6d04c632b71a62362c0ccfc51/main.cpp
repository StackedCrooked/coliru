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
    
    std::unordered_map<T, node> root;
};

int main() {
    tree<int> arf;
    
    
}
#include <unordered_map>
#include <vector>

template <typename TK, typename TV>
class unordered_tree {
    typedef std::hash<TK> TH;
    typedef std::equal_to<TK> TKEq;
    
private:
    struct node {
    public:
        TV value;
        // Must I use pointers? =[
        std::unordered_map<TK, node, TH, TKEq> children;
        
	};
    
    std::unordered_map<TK, node, TH, TKEq> root;
    
public:
    
    unordered_tree () {
        
    }

};

int main() {
    unordered_tree<int, int> meow;
    
    
}
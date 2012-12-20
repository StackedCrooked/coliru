#include <vector>
    #include <initializer_list>
    
    class GenericNode {
    public:
        template<class ...Ts>
        GenericNode(Ts... inputs) 
            :inputs_{inputs...} {} //well that's easy
    private:
        std::vector<GenericNode*> inputs_;
    };
    int main() {
        GenericNode* ptr;
        GenericNode node{ptr, ptr, ptr, ptr};
    }
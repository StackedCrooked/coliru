    #include <vector>
    #include <initializer_list>
    
    class GenericNode {
    public:
        GenericNode(std::initializer_list<GenericNode*> inputs) 
            :inputs_(inputs) {} //well that's easy
    private:
        std::vector<GenericNode*> inputs_;
    };
    int main() {
        GenericNode* ptr;
        GenericNode node{ptr, ptr, ptr, ptr};
    }
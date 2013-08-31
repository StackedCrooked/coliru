#include <vector>
 
template<class T>
using Alias = T;
     
class GenericNode {
public:
    template<typename T, class ...Ts>
    GenericNode(T&& head, Ts&&... inputs) 
        : GenericNode(std::forward<Ts>(inputs)...)
    {
        inputs_.push_back(head);
    }
private:
    GenericNode() {}
    std::vector<GenericNode*> inputs_;
};
int main() {
    GenericNode* ptr;
    GenericNode node(ptr, ptr, ptr, ptr);
}
 #include <vector>
 
template<class T>
using Alias = T;
     
class GenericNode {
public:
    template<class ...Ts>
    GenericNode(Ts... inputs) { //SFINAE might be appropriate
         using ptr = GenericNode*;
         Alias<char[]>{(
             inputs_.push_back(ptr(inputs))
             ,'0')...,'0'}; //second part of magic unpacker
    }
private:
    std::vector<GenericNode*> inputs_;
};
int main() {
    GenericNode* ptr;
    GenericNode node(ptr, ptr, ptr, ptr);
}
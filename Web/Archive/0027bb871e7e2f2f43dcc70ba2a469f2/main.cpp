 #include <vector>
 
template<class T>
using Alias = T;
     
class GenericNode {
public:
    template<class ...Ts>
    GenericNode(Ts... inputs) { //SFINAE might be appropriate
         Alias<char[]>{( //first part of magic unpacker
             inputs_.push_back(GenericNode*(inputs))
             ,'0')...,'0'}; //second part of magic unpacker
    }
private:
    std::vector<GenericNode*> inputs_;
};
int main() {
    GenericNode* ptr;
    GenericNode node(ptr, ptr, ptr, ptr);
}
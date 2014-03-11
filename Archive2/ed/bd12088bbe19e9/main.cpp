#include <iostream>
#include <string>
#include <map>
#include <memory>


class Node;
typedef std::shared_ptr<Node> NodePtr;

class Node
{
    void SomeOtherMethod() {
        // Access some member
        std::cout << "SomeOtherMethod() @" << this << "; size: " << _childNodes.size() << std::endl;
    }

public:
    std::map<std::string, NodePtr> _childNodes;
    
    Node() = default;
    
    ~Node() {
        std::cout << "Node " << this << " destroyed." << std::endl;
    }

    bool GetChildByKeyName(/*In*/ const std::string& key, /*Out*/ NodePtr& spChild)
    {
        bool result = false;
        auto itor = _childNodes.find(key);
        if (itor != _childNodes.end())
        {
            if(spChild.get() == this) std::cout << "spChild.get() == this" << std::endl;
            
            std::cout << "spChild before: " << spChild.get() << std::endl;
            
            spChild = itor->second;
            
            std::cout << "spChild after: " << spChild.get() << std::endl;
            
            result = true;
            SomeOtherMethod();
        }
        return result;
    }
};


int main() {
    NodePtr spNode = std::make_shared<Node>();
    spNode->_childNodes.emplace("test", std::make_shared<Node>());
    
    std::cout << "spNode before: " << spNode.get() << std::endl;
    spNode->GetChildByKeyName("test", spNode);
    std::cout << "spNode after: " << spNode.get() << std::endl;
}

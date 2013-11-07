#include <string>
#include <iterator>
#include <iostream>
#include <algorithm>
#include <array>
#include <memory>
 
class Node
{
public:
    Node () {};
    ~Node () {};
    std::string name;
};

int main()
{
    Node* node = new Node;
    node->name = "toto";
    Node* x = node;
    
    std::shared_ptr<Node> sp = std::make_shared<Node>(*node);
    
    std::cout << x->name << std::endl;
}
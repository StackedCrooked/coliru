#include <iostream>
#include <memory>
#include <vector>

class Node
{
    int SomeValue;
public:
    Node(int Value)
    : SomeValue(Value)
    {}

    virtual ~Node()
    {
        // Cleanup the node
    }
};

class NodeFactory
{
    std::vector<std::unique_ptr<Node>> Nodes;
public:
    template<typename T>
    void CreateNode(int Value)
    {
        Nodes.push_back(std::unique_ptr<T>(new T(Value)));
    }
};

struct Node2 : Node 
{
    using Node::Node;
};

int main()
{
    NodeFactory nf;
    nf.CreateNode<Node>(10);
    nf.CreateNode<Node2>(20);
}

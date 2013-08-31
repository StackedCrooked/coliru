class Node
{
public:
    Node(Node & parent) : _parent(&parent) {}
    
    const Node & parent() const { return *parent; }
    
    Node & parent() { return *parent; }

private:
    Node * _parent;
};
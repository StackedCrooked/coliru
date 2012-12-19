class Node
{
public:
    Node(Node & parent) : _parent(&parent) {}
    
    const Node & parent() const { return *_parent; }
    
    Node & parent() { return *_parent; }

private:
    Node * _parent;
};
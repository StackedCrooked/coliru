


class Node
{
public:
    Node(Node & parent) : parent(&parent) {}
    
    const Node & parent() const { return *parent; }
    
    Node & parent() { return *parent; }

private:
    Node * parent;
};
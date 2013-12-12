template<typename T>
class Tree
{
public:
    using value_type = T;

    class Node
    {
    private:
        Node* right;
        value_type value;
    public:
        void Node_Function(Tree*);
    };
    Node* top;

public:
    void X_f()
    {

    }
};

template<typename T>
void Tree<T>::Node::Node_Function(Tree* p)
{
    top = right; //I suppose to get error here like "error : no object of type Tree specified"
}

int main() {
    Tree<int>::Node n;
    n.Node_Function(0);
}
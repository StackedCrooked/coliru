#include <iostream>
#include <typeinfo>

using namespace std;

struct NodeBase {
    virtual ~NodeBase(){}
};

template<typename T>
struct Node: public NodeBase {
    T data;
    NodeBase *parent;

    Node(T data, NodeBase* parent = nullptr)
        : data(data), parent(parent)
    {}

    ~Node(){}
};

template<typename T>
Node<T>* AsNode(NodeBase* b){return (Node<T>*)b;}

void PrintNodeBase(NodeBase* b)
{
    if(typeid(*b) == typeid(Node<int>))
        cout << AsNode<int>(b)->data << endl;
    if(typeid(*b) == typeid(Node<char>))
        cout << AsNode<char>(b)->data << endl;
    return;
}
    

int main()
{
    Node<int>  n2(63);
    Node<char> n1('A', &n2);
    n2.parent = &n1;

    PrintNodeBase(n1.parent); //pointer to n2
    PrintNodeBase(n2.parent); //pointer to n1

    return 0;
}
#include <iostream>

template<typename T>
class Tree{
    friend void foo(); //HERE
    
    using value_type = T;                   // member alias
    enum Policy { rb, splay, treeps };      // member enum
    class Node{                             // member class
        Node* right;
        Node* left;
        value_type value;
    public:
        void f(Tree*);
    };
    Node* top;
    
public:
    void g(Node*);
};

template<typename T>
void Tree<T>::Node::f(Tree* p)
{
  //top = right;                            // error: no object of type tree specified
    p->top = right;                         // OK
    value_type v = left->value;             // OK: value_type is not associated with an object
}

template<typename T>
void Tree<T>::g(Tree::Node* p)
{
  //value_type val = right->value;          // error: no object of type Tree::Node
    value_type v = p->right->value;         // error: Node::right is private
    p->f(this);                             // OK
}    

//HERE
void foo() {
    Tree<int>::Node n;
    Tree<int> t;
    t.g(&n);
}

int main()
{    
}
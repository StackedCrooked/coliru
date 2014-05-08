#include <iostream>
#include <string>
#include <memory>

class TreeNode;
typedef std::unique_ptr<TreeNode> NodePtr;

class TreeNode {                          // Leaf Node
    TreeNode(TreeNode const&);            // no copy
    TreeNode& operator=(TreeNode const&); // no copy

public:
    TreeNode(char operation, int data) 
        : operation(operation), data(data) { }

    int  Evaluate()  const;
    void InOrder()   const;
    void PreOrder()  const;
    void PostOrder() const;

    NodePtr left, right;
    char operation;
    int data;
};

NodePtr createExpressionTree() { //creates binary expression tree
    NodePtr root(new TreeNode('*', 3));
    root->left        .reset(new TreeNode('+', 5));
    root->left->left  .reset(new TreeNode('2', 2));
    root->left->right .reset(new TreeNode('3', 3));
    root->right       .reset(new TreeNode('5', 5));

    return root;
}

int TreeNode::Evaluate() const { //Evaluates tree

    switch(operation) { //switch statement to decide what operator is being used
        case '+': return left->Evaluate() + right->Evaluate();
        case '-': return left->Evaluate() - right->Evaluate();
        case '*': return left->Evaluate() * right->Evaluate();
        case '/': return left->Evaluate() / right->Evaluate();
    }
    return data;
}

void TreeNode::InOrder() const { //traverses the tree InOrder
    if (left) left->InOrder();
    std::cout << operation << " ";
    if (right) right->InOrder();
}

void TreeNode::PreOrder() const { //traverses the tree PreOrder
    std::cout << operation << " ";
    if (left)  left->PreOrder();
    if (right) right->PreOrder();
}

void TreeNode::PostOrder() const { //traverses the tree PostOrder
    if (left)  left->PostOrder();
    if (right) right->PostOrder();
    std::cout << operation << " ";
}

int main() {                       //main program
    NodePtr root = createExpressionTree();
    std::cout << "The Answer is: " << root->Evaluate();

    std::cout << "\nIn InOrder     ";
    root->InOrder();

    std::cout << "\nIn PreOrder  ";
    root->PreOrder();

    std::cout << "\nIn PostOrder ";
    root->PostOrder();
}

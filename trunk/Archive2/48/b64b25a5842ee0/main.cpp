#include<memory>
#include<cmath>
#include<iostream>

struct BST
{
    struct Node
    {
    public:
        Node* parent;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;

        int height()
        {
            //I'm assuming both nodes are either set or unset
            if(left == nullptr && right == nullptr) 
            {
                return 0;
            }
            else
            {
                return std::max(left->height(), right->height()) + 1;
            }
        }
    };
    std::unique_ptr<Node> root;
};

int main()
{
    BST bst;
    //contruct root node
    bst.root = std::make_unique<BST::Node>();

    //contruct child nodes of root
    bst.root->left = std::make_unique<BST::Node>();
    bst.root->right = std::make_unique<BST::Node>();

    //contruct child nodes of left child of root
    bst.root->left->left = std::make_unique<BST::Node>();
    bst.root->left->right = std::make_unique<BST::Node>();

    //prints depth of root node, which is 2
    std::cout<<bst.root->height()<<std::endl;
}

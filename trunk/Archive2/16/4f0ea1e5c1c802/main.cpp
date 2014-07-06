#include <iostream>
#include <memory>

template<class T>
class BinarySearchTree{
    struct TreeNode;
    typedef std::unique_ptr<TreeNode> spTreeNode;
    struct TreeNode{
        T data;
        spTreeNode  left;
        spTreeNode  right;
        TreeNode(const T & value):data(value),left(nullptr),right(nullptr){}
    };



    spTreeNode root;
    bool insert(spTreeNode &node);
    void print(const spTreeNode&) const ;
public:
    BinarySearchTree();
    void insert( const T & node);
    void print()const;
};

template<class T>
BinarySearchTree<T>::BinarySearchTree():root(nullptr){}

template<class T>
void BinarySearchTree<T>::insert(const T & ref)
{
    std::unique_ptr<TreeNode> node(new TreeNode(ref));
    if (root == nullptr) {
        root = std::move(node);
    } else {
        TreeNode* temp = root.get();
        TreeNode* prev = root.get();
        while (temp != nullptr) {
            prev = temp;
            if (temp->data < ref)
                temp = temp->right.get();
            else
                temp = temp->left.get();
        }
        if (prev->data < ref)
            prev->right = std::move(node);
        else
            prev->left = std::move(node);
    }
}

template<class T>
void BinarySearchTree<T>::print()const
{
    print(root);
}

template<class T>
void BinarySearchTree<T>::print(const std::unique_ptr<TreeNode> &node) const
{
    if(node == nullptr) return;
    print(node->left);
    std::cout << node->data<< std::endl;
    print(node->right);
}

int main()
{
    BinarySearchTree<int> bst;
    bst.insert(13);
    bst.insert(3);
    bst.insert(5);
    bst.insert(31);
    bst.print();
    return 0;
}
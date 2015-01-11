#include <iostream>

////    START OF HEADER

template< class Element >
class BinaryTree
{
public:
    BinaryTree() { root = NULL; }
    
    bool insert(const Element& el)       { return insert(root, el); }
    bool search(const Element& el) const { return search(root, el); }
    void display() const { display(root); }

private:
    struct Node
    {
        Element info;
        Node *  left;
        Node *  right;
    };
    
    Node *  root;
    
    bool search(Node* node, const Element& el) const
    {
        if (node == NULL)
            return false;
        else if (el == node->info)
            return true;
        else if (el < node->info)
            return search(node->left, el);
        else
            return search(node->right, el);
    }
    
    bool insert(Node* &node, const Element& el)
    {
        if (node == NULL)
        {
            node = new Node();
            node->left  = NULL;
            node->right = NULL;
            node->info  = el;
            return true;
        }
        else if (el == node->info)
            return false;
        else if (el < node->info)
            return insert(node->left, el);
        else
            return insert(node->right, el);
    }
    
    // If you want to define it outside...
    void display(Node* aRoot) const;
};

// you can... but this MUST also be #included into the code when
// you use it, or the compiler can't figure out the definition.
template< class Element >
void BinaryTree<Element>::display(Node* node) const
{
    if (node != NULL)
    {
        display(node->left);
        std::cout << node->info << std::endl;
        display(node->right);
    }
}

////    END OF HEADER

////    START OF CODE
int main()
{
    BinaryTree<int> bin_tree;
    std::cout << "BinaryTree::insert" << std::endl;
    std::cout << bin_tree.insert(1); // true
    std::cout << bin_tree.insert(3); // true
    std::cout << bin_tree.insert(4); // true
    std::cout << bin_tree.insert(3); // false
    std::cout << std::endl << std::endl;
    
    std::cout << "BinaryTree::display" << std::endl;
    bin_tree.display();
    std::cout << std::endl;
    
    
    bin_tree.insert(6);
    
    std::cout << "BinaryTree::search" << std::endl;
    std::cout << "has 0 = " << bin_tree.search(0) << std::endl;
    std::cout << "has 1 = " << bin_tree.search(1) << std::endl;
    std::cout << "has 2 = " << bin_tree.search(2) << std::endl;
    std::cout << "has 3 = " << bin_tree.search(3) << std::endl;
    std::cout << "has 4 = " << bin_tree.search(4) << std::endl;
    std::cout << "has 5 = " << bin_tree.search(5) << std::endl;
    std::cout << "has 6 = " << bin_tree.search(6) << std::endl;
}
////    END OF CODE
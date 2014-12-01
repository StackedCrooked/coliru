#include <iostream>
#include <algorithm>

class Node
{
public:
    Node(int data, Node* left = nullptr, Node* right = nullptr)
        : data(data)
        , left(left)
        , right(right)
    { }
    
    Node& setLeft(int n)  { left  = new Node(n); return *left;  }
    Node& setRight(int n) { right = new Node(n); return *right; }
    
    int data{0};
    Node* left;
    Node* right;
};

bool myisBST(Node* node, std::vector<int> v);

bool myisBST(Node* node)
{
    return myisBST(node, std::vector<int>());
}

bool myisBST(Node* node, std::vector<int> v)
{
    if (node)
    {
        if (node->left)
            return myisBST(node->left, v);
            
        v.push_back(node->data);
        
        if (node->right)
            return myisBST(node->right, v);
            
        return true;
    }
    
    return std::is_sorted(v.begin(), v.end());
}

int main()
{
    // ============= Set the values //
    Node root(50);
    
    auto& l  = root.setLeft(25);
    auto& r  = root.setRight(75);
    l.setLeft(1);
    l.setRight(12);
    r.setLeft(62);
    r.setRight(-99);
    
    // ============= Test ======== //
    std::cout << std::boolalpha;
    
    std::cout << "Is BST: " << myisBST(&root);
    // ============================== //
}
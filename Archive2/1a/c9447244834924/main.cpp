#include <iostream>

struct node {
    int data;
    node *left, *right;
};

void copy(node *& dest, node * root)
{
  if(!root)
  {
      dest = NULL;
      return;
  }
  else
  {
      dest = new node;
      dest -> data = root -> data;
      copy(dest -> left, root -> left);
      copy(dest -> right, root -> right);
  }
}

std::ostream &operator << (std::ostream &oss, const node *tree) {
    if (tree != nullptr) {
        oss << tree->left << tree->data << " " << tree->right;
    }
    return oss;
}

void delTree(node *& tree) {
    if (tree != nullptr) {
        delTree(tree->left);
        delTree(tree->right);
        delete tree;
        tree = nullptr;
    }
}

int main()
{
    node *tree = new node{3, new node{2, new node {1, nullptr, nullptr}, nullptr}, new node{4, nullptr, nullptr}};
    node *cp;
    std::cout << tree << std::endl;
    copy(cp, tree);
    std::cout << tree << std::endl;
    std::cout << cp << std::endl;
    
    delTree(tree);
    delTree(cp);
    
    std::cout << tree << std::endl;
    std::cout << cp << std::endl;
    return 0;
}
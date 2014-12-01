#include <iostream>

template <class K, class V> class TreeNode {
  public:
  TreeNode(K k, V v): key(k), value(v), left(0), right(0) {}

  K       key;
  V       value;
  TreeNode<K,V>   *left;
  TreeNode<K,V>   *right; 
};

template<class K, class V> class Tree {
    public:
    TreeNode<K,V> *root;
    
    void insert (K k, V v) {
        TreeNode<K,V> * treeNode = new TreeNode<K,V> (k,v);
        TreeNode<K,V> *temp=NULL;
        TreeNode<K,V> *prev=NULL;
        temp = root;
        
        while(temp) { // crashes in this loop, even if I remove loop and have it only activate once
        prev = temp;
        if (temp->key < treeNode->key)
          temp = temp->right;
        else
          temp = temp->left;
        }
        
        if (prev==NULL)
        root = treeNode;
        else {
        if (prev->key<treeNode->key)
          prev->right = treeNode;  
        else
          prev->left = treeNode;
        }
    }
};

int main() {
    Tree<std::string,std::string> t;
    t.root = nullptr;
    t.insert("bob", "bobdata");
    
    return 0;
}
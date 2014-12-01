#include <string>
#include <iostream>

template <class K, class V> class TreeNode {
  public:
  TreeNode(K k, V v): key(k), value(v), left(0), right(0) {}

  K       key;
  V       value;
  TreeNode<K,V>   *left;
  TreeNode<K,V>   *right;
  template <class X, class Y> friend std::ostream & operator 
  << (std::ostream &s,const TreeNode<X,Y> &t);    
};


TreeNode<std::string, std::string>* root = nullptr;

template <class K, class V> 
void insert (K k, V v) {
  TreeNode<K,V> * treeNode = new TreeNode<K,V> (k,v);
  TreeNode<K,V> *temp=NULL;
  TreeNode<K,V> *prev=NULL;
  temp = root;

  while(temp) { // crashes in this loop, even if I remove loop and have it only activate once
    prev = temp;
    if (temp->key < treeNode->key)  //MARKER
      temp = temp->right;           //MARKER
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

template <class X, class Y> 
std::ostream & operator << (std::ostream &s,const TreeNode<X,Y> &t)
{
    s << "[" << t.key << ":" << t.value << "(";
    if (t.left) s << *t.left;
    s << ",";
    if (t.right) s << *t.right;
    s << ")]";
    return s;
}

int main()
{
    insert<std::string,std::string>("han", "solo");
    insert<std::string,std::string>("darth", "vader");
    insert<std::string,std::string>("luke", "skywalker");
    insert<std::string,std::string>("yoda", "master");
    insert<std::string,std::string>("leia", "organa");
    insert<std::string,std::string>("boba", "fett");
    insert<std::string,std::string>("r2", "d2");
    insert<std::string,std::string>("obi-wan", "kenobi");
    insert<std::string,std::string>("mace", "windu");
    insert<std::string,std::string>("jabba", "hutt");
    insert<std::string,std::string>("jar jar", "binks");
    
    std::cout << *root;
}
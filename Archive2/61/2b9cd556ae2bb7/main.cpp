#include <cstddef>
template <class Key, class Value>
class BinaryTreeNode
{
  
  public:
    BinaryTreeNode(const Key & key, const Value & value, BinaryTreeNode * father) : m_key(key), m_value(value), m_father(father), m_left(NULL), m_right(NULL)
    {
        m_height =  m_father ? m_father->m_height + 1 : 1;
    }
    bool isLeaf(){ return !m_right && !m_left; }
    BinaryTreeNode * getLeftSon(){ return m_left; }
    BinaryTreeNode * getRightSon(){ return m_right; }
    BinaryTreeNode * getFather(){ return m_father; }
    unsigned int getHeight(){ return m_height; }
   
   private:
    Key m_key;
    Value m_value;
    BinaryTreeNode<Key, Value> * m_left;
    BinaryTreeNode<Key, Value> * m_right;
    BinaryTreeNode<Key, Value> * m_father;
    unsigned int m_height;
};

template <class Key, class Value>
class BinaryTree
{
    
};

template <class Key, class Value>
class BinarySearchTree : public BinaryTree<Key, Value>
{
    
};

int main()
{
  
}

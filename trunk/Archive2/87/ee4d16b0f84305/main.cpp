template <typename T>
struct Tree
{
};

template <typename T, typename U>
struct BinaryTreeNode
{
};

#define NULL 0

template <class T, template <class> class NodeType = BinaryTreeNode>
class BinaryTree : public Tree<T>
{
  int size;
  NodeType<T> *root;

  public:

  ~BinaryTree()
  {
    if(root != NULL)
    {
      delete root;
    }
  }
  BinaryTree()
  {
    this->size = 0;
    this->root = NULL;
  }

  bool create();
  bool insert(T p);
  
};

template <typename T, template <class> class U>
bool BinaryTree<T, U>::insert(T data)
{
  U<T> *bNode = new U<T>(data);
}
#include <iostream>
#include <stack>
#include <functional>

using namespace std;

template<typename T>
struct Tree
{
    struct Node
    {
        T Value;
        Node * Left;
        Node * Right;

        Node(T value) : Value(value), Left(nullptr), Right(nullptr) {}

        virtual ~Node()
        {
            if (Left) delete Left;
            if (Right) delete Right;
        }
    };

    Node * Root;

    Tree() : Root(nullptr) {}

    virtual ~Tree() { if (Root) delete Root; }
};

template<typename T> void insert(typename Tree<T>::Node * node, T const & value)
{
    typename Tree<T>::Node ** selected = &(value < node->Value ? node->Left : node->Right);

    if (*selected)
        insert(*selected, value);
    else
        *selected = new typename Tree<T>::Node(value);
}

template<typename T> void insert(Tree<T> & tree, T value)
{
    if (!tree.Root)
        tree.Root = new typename Tree<T>::Node(value);
    else
        insert(tree.Root, value);
}

template<typename T, typename D, typename G>
bool ts(Tree<T> const & tree, T const value, D & ds, G getter)
{
    if (!tree.Root) return false;

    ds.push(tree.Root);
    while (!ds.empty())
    {
        auto const current = (ds.*getter)(); //note the syntax
        ds.pop();

        if (current->Value == value) return true;

        if (current->Left) ds.push(current->Left);
        if (current->Right) ds.push(current->Right);
    }
    return false;
}

template<typename T>
bool dfs(Tree<T> const & tree, T const value)
{
    typedef typename Tree<T>::Node const * DataStructureContent;
    typedef stack<DataStructureContent> DataStructure;
    
    typedef typename DataStructure::reference reference;
    typedef reference (DataStructure::*top_type)();//non-const version
    
    DataStructure ds;
    return ts(tree, value, ds, static_cast<top_type>(&DataStructure::top) ); //pass pointer to member
}

int main()
{
    Tree<int> tree;
    insert(tree, 5);
    insert(tree, 2); insert(tree, 1); insert(tree, 3);
    insert(tree, 7); insert(tree, 6); insert(tree, 9);
    cout << "DFS(7) -> " << dfs(tree, 7) << endl;
    cout << "DFS(8) -> " << dfs(tree, 8) << endl;
    return 0;
}
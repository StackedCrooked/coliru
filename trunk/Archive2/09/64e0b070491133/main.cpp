#include <functional>
#include <iostream>
#include <stack>

using namespace std;

// Iterative DFS for a binary tree.
// Tree must be a (smart) pointer to a struct with 'value', 'left', and 'right'
// members. 
template <typename Tree> void dfs(Tree t, function<void(decltype(t->value))> fVisit)
{
    stack<Tree> todo;

    for ( ; ; )
    {
        while (t != nullptr)
        {
            todo.push(t);
            t = t->left;
        }

        if (todo.empty()) break;

        fVisit(todo.top()->value);
        t = todo.top()->right;
        todo.pop();
    }
}

struct Node
{
    Node(char v, Node *l = nullptr, Node *r = nullptr) : value(v), left(l), right(r) {}

    char value;
    Node *left;
    Node *right;
};

int main()
{
    dfs(static_cast<Node*>(nullptr), [](char c){ cout << c; });
    cout << endl;

    dfs(new Node('x'), [](char c){ cout << c; });
    cout << endl;

    dfs(new Node('x', new Node('a', new Node('1'), new Node('2')), new Node('b', new Node('3'), new Node('4'))), [](char c){ cout << c; });
}

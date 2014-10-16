#include <iostream>
#include <iomanip>
#include <stack>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <vector>
#include <limits>
#include <time.h>
#include <random>
#include <functional>
#include <algorithm>

using namespace std;

struct Node
{
    Node * left = nullptr;
    int data = 0;
    Node * right = nullptr;
    Node() { }
    Node(int d) : data(d) { }
    Node(int d, Node * r)  : data(d), right(r) { }
    Node(Node * l, int d)  : left(l), data(d) { }
    Node(Node * l, int d, Node * r) : left(l), data(d), right(r) { }
    ~Node( ) { delete left; delete right; }
};

void VertSum(Node * n, map<int, int>& m, int currIndx)
{
    if(n != nullptr)
    {
        VertSum(n->left, m, currIndx - 1);
        m[currIndx] = m[currIndx] + n->data;
        VertSum(n->right, m, currIndx + 1);
    }
}

int main()
{
    Node * np = new Node
    (
        new Node
        (
            new Node(9),
            5,
            new Node
            (
                new Node(1),
                7,
                new Node
                (
                    new Node(2),
                    12
                )
            )
        ),
        8,
        new Node
        (
            4,
            new Node
            (
                new Node(3),
                11
            )
        )
    );
    
    std::map<int, int> m;
    
    VertSum(np, m, 0);
    
    for (auto p : m)
        cout << setw(2) << setfill(' ') << p.first << "  " <<  setw(2) << setfill(' ') << p.second << endl;

    return 0;
}

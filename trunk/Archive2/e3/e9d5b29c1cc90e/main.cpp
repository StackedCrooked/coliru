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
#include <tuple>

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
/*
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
*/

unsigned findMissing(vector<unsigned> & vec)
{
    unsigned ret = 0;
    if (vec.size() == 0)
        ret = 0;
    else if (vec[0] == 2)
        ret = 1;
    else
    {
        unsigned beg = 0;
        unsigned end = vec.size();
        unsigned mid = (end + beg) / 2;
        cout << " beg: " << beg << " mid: " << mid << " end: " << end << endl;
        while (beg < end - 1)
        {
            if (vec[mid] > mid + 1)
                end = mid;
            else
                beg = mid;
            mid = (end + beg) / 2;
            cout << " beg: " << beg << " mid: " << mid << " end: " << end << endl;
        }
        ret = mid + 2;
    }
    return ret;
}

struct V
{
    virtual void f() { cout << "V::f" << endl; }
    virtual void g() { cout << "V::g" << endl; }
    
    V() { cout << "V::V" << endl; f(); g(); }
};

struct O
{
    O (V* v) { cout << "O::O" << endl; v->f(); v->g(); }
};

struct A : virtual V
{
    O o;
    virtual void f() { cout << "A::f" << endl; }
    A() : o(this) { cout << "A::A" << endl; f(); g(); }
};

struct B : virtual V
{
    O oo;
    virtual void g() { cout << "B::g" << endl; }
    B() : oo(this) { cout << "B::B" << endl; f(); g(); }
    B(V*, A*);
};

struct D : B, A
{
    virtual void f() { cout << "D::f" << endl; }
    virtual void g() { cout << "D::g" << endl; }
    D() { cout << "D::D" << endl; f(); g();  }
};

B::B(V* v, A* a) : oo(this)
{
    f(); // calls V::f, not A::f
    g(); // calls B::g, not D::g
    v->g(); // v is base of B, the call is well-defined, calls B::g
    a->f(); // undefined behavior, a’s type not a base of B
}
int main()
{
    D d;    
    
    vector<unsigned> vec1;
    vec1.push_back(1);
    vec1.push_back(2);
    vec1.push_back(3);
    vec1.push_back(4);
    vec1.push_back(5);
    vec1.push_back(6);
    vec1.push_back(7);
    vec1.push_back(9);

    cout << "Missing: " << findMissing(vec1) << endl;


    // preconditions as stated - no param verification
    int size, diff;
    cin >> size;
    cin >> diff;
    
    // psuedo
    vector<unsigned> vec;
    unordered_set<int> hash;
    int i;
    while (cin >> i)
        vec.push_back(i);

    unsigned ret = 0;
    for (auto i : vec)
    {
        if (hash.find(diff - i) != hash.end())
            ++ret;
        hash.insert(i);
    }
    
    cout << ret << endl;
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    return 0;
}

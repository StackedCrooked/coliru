#include <iostream>
using namespace std;

class Node
{
    public: int x;
};

class Model : protected Node
{
    public: void foo () { x++; }
};

int main ()
{
    Node n;
    Model m;
    
    cout << n.x;
    //cout << m.x;
    m.foo();
}
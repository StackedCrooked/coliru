#include <iostream>
using namespace std;

struct B {
    int x = 0;
    B& operator=(int a) {
        cout << __PRETTY_FUNCTION__ << ' ' << (int)a << endl;
        x = a;
        return *this;
    }
};

class Index
{
    int state;
public:
    Index(int s) : state(s) {}
    Index& operator++()
    {
        cout << __PRETTY_FUNCTION__ << endl;
        state++;
        return *this;
    }
 
    operator int() const
    {
        cout << __PRETTY_FUNCTION__ << endl;
        return state;
    }
};

struct A {
    B& operator[](int i) {
        cout << __PRETTY_FUNCTION__ << ' ' << i << endl;
        return bb[i];
    }
    
    B bb[5];
};

int main()
{
    A a;
    Index i(2);
    a[++i] = i;
   
    for (auto& b : a.bb)
        cout << b.x << ' ';
    cout << endl << endl;
    return 0;
}
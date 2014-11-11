#include <iostream>
using namespace std;



class Index
{
public:
    int state;
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

struct B {
    int x = 0;
    B& operator=(int a) {
        cout << __PRETTY_FUNCTION__ << ' ' << a << endl;
        x = a;
        return *this;
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
    Index i = 2;
    a[++i] = i;
    // try also this:
    // a[i] = ++i;
   
    for (auto& b : a.bb)
        cout << b.x << ' ';
    cout << endl << endl;
    return 0;
}
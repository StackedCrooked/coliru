#include <iostream>
#include <cstring>

using std::cout;
using std::endl;

struct X
{
    int a = 6;
    X(){ }
    X(const X&)
    {
        cout << "X()" << endl;
    }
};

X a;
X b;
int main()
{
    a.a = 10;
    std::memcpy(&b, &a, sizeof(X));
    cout << b.a << endl;
}
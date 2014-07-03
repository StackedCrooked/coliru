#include <iostream>

using namespace std;

struct Foo {
    int x, a, b, c, d, e;
};

int main() {
    Foo foo = { 1, 2, 3, 4, 5, 6 };
    int* pfoo = (int*)&foo;
    
    int structMembers = sizeof(Foo) / sizeof(int);
    for (int i = 0; i < structMembers; i++)
    {
        cout << pfoo[i] << endl;
    }
}
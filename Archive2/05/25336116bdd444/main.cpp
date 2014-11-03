#include <iostream>

using namespace std;

struct strct
{
    virtual void func() {}
};

struct strct2 : strct
{
    virtual void func(int) override {}
};

int main() {
    cout << "Hello, World!" << endl;
    return 0;
}
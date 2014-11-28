#include <iostream>
using namespace std;

void foo()
{
    int i = 0xffffffff;
    cout << i << endl;
}

void bar()
{
    bool b;
    if(b)
        cout << "true" << endl;
    if(!b)
        cout << "false" << endl;
}

int main()
{
    foo();
    bar();
}
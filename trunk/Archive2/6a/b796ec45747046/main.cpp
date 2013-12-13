
#include <iostream>

using namespace std;

class base
{
    int i;
public:
    void f() 
    {
        i++;
        cout << "base f:" <<endl;
    }
};


int main()
{
    base *b;
    b->f();
}
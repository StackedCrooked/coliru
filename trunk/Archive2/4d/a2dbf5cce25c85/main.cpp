#include <iostream>

using std::cout;
using std::endl;

struct B
{
    int b;
    B(int b) : b(10)
    {
         B::b = b;
    }
};

B b(4);

int main()
{
    cout << b.b << endl; //4
}
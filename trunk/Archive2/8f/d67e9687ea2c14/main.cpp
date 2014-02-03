#include <iostream>
using namespace std;

int main()
{
    int *a = new int, *b = new int;
    *a = 10;
    *b = 20;
    cout << "value of a is " << *a << "  and value of b is " << *b << endl;
    delete a, b;
    cout << "value of a is " << *a << "  and value of b is " << *b << endl;
}

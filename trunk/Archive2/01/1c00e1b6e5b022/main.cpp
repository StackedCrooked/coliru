#include <iostream>
using namespace std;

void f(int& x)
{
    cout << "l value" << endl;
}

void f(int&& x)
{
    cout << "r value" << endl;
}

int main()
{
    int a = 0;
    f((int)a);
}
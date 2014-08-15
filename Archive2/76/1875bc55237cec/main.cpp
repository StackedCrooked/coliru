#include <iostream>
using namespace std;

struct A
{
    int a;
    A(int a)
    {
        A::a = a; //Unclear, because in that case we just applying scope resolution operator to A and does
        this -> a = a; //It is clear, because this points to a current object
    }
};

int main()
{
    A a(4);
    cout << a.a;
}
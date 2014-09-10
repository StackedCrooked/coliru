#include<iostream>
using namespace std;

class A
{
private:
    static int x;
    int y;
public:
    A(int i) { x = i; y = -i; }
    static int put_x(A a) { return x + a.y; }
};

int A::x = 5;
int main()
{
    A a(7);
    cout << A::put_x(3);
    return 0;
}
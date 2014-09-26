#include <iomanip>
#include <iostream>

using namespace std;
struct X
{
    bool b;
    int a;
};
int X::* a =&X::a;
bool X::* b = &X::b;
X x;

int main()
{
    cout << std::boolalpha << a << b;
}
#include <iostream>
using namespace std;

template <typename T>
class A
{
    public:
    void foo(){cout << "Primary" << endl;}
};

template <>
void A<int>::foo()
{
    cout << "Spec" << endl;
}

int main()
{
    A<double>{}.foo();
    A<int>{}.foo();
    return 0;
}
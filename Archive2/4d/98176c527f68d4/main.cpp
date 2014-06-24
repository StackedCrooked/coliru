#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

class A {
    public:
    A(int) { }
};

int main()
{
    A a[10] = A(1);
    return 0;
}
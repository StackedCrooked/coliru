#include <iterator>
#include <iostream>
#include <algorithm>
using namespace std;

template<class T>
class B {
};

template<int i = 5>
class A : public B<A<i>> {
};


int main()
{
    A<3> a;
    A<> b;
}

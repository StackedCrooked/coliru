#include<iostream>
#include<cassert>
template <typename T1, typename T2 = int>
T2 count (T1 const& x);
class MyInt {};
class Container {};
void test (Container const& c)
{
    int k = 0;
    int i = count(c);
    MyInt j = count<Container, MyInt>(c);
    assert(k == i);
}

int main()
{
    Container c;
    test(c);
}
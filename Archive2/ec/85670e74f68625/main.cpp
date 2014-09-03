#include <vector>

class A {};

int main()
{
    std::vector<A> v;
    A a;
    v.push_back(a);
}

#include <set>
#include <functional>

class A {};

int main()
{
    A a;
    A * p = &a;
    const A * cp = &a;

    std::set<A*, std::less<>> s;
    s.insert(p);
    s.find(cp);
}
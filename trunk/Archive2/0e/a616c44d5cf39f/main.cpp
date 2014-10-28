#include <set>
#include <iostream>

class Foo
{
    int x;
};

int main()
{
    int n = 100;
    std::set<Foo*> ptrs;
    for (int i = 0; i < n; ++i)
    {
        Foo * p = new Foo();
        ptrs.insert(p);
        delete p;
    }
    
    std::cout << n - ptrs.size() << " reused addresses for " << n << " new/delete pairs." << std::endl;
}

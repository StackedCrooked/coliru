#include <vector>
#include <algorithm>
#include <functional>

struct Foo {};

void
add_each(std::vector<std::vector<Foo*> > &vv, const Foo *f)
{
    for_each(vv.begin(), vv.end(), std::bind2nd(std::mem_fun_ref(&std::vector<Foo*>::push_back), f));
}

int main()
{
    std::vector<std::vector<Foo*> > foos;
    Foo f;
    add_each(foos, &f);
}

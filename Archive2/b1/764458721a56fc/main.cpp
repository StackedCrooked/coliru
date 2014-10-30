#include <list>

std::list<int> f(std::list<int> d = {}) { return d; }

int main ()
{
    std::list<int> d = f();
}
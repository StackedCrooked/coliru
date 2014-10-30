#include <list>

std::list<int> f(std::list<int> d = {1, 2, 3}) { return d; }

int main ()
{
    std::list<int> d = f();
}
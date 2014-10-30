#include <iostream>
#include <list>
using namespace std;

list<int> g(list<int> d = {}) { return d; }

int main ()
{
    auto d = g();
}
#include <initializer_list>
#include <forward_list>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <list>
using namespace std;

int counter = 0;

struct T
{
    int value;
    T(int x = 0) : value(x) {}
    T(const T &x)
    {
        ++counter;
        value = x.value;
    }
    T &operator=(const T &x)
    {
        ++counter;
        value = x.value;
        return *this;
    }
};
auto pred = [](const T &x){return x.value;};

template<typename Container>
void test()
{
    Container l = {0, 1, 1, 1, 1};
    counter = 0;
    partition(begin(l), end(l), pred);
    cout << "Moves count: " << counter << endl;
}

int main()
{
    test<forward_list<T>>();
    test<list<T>>();
}
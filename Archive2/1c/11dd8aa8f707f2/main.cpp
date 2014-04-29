#include <iostream>
#include <set>

using namespace std;

template<class T, class Q = greater<T> >
class MySet
{
public:
    typedef typename set<T, Q>::iterator iterator;
    set<T, Q> tset;
    void insert(T value)
    {
        tset.insert(value);
    }
};

int main()
{
    MySet<int> intset;
    intset.insert(5);
    intset.insert(10);
    MySet<int>::iterator p;
}
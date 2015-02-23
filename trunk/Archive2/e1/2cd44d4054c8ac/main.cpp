#include <iostream>
#include <initializer_list>
#include <functional>
#include <numeric>
#include <list>
#include <vector>

using namespace std;

template<class Fn, typename T>
void foo(Fn f, T&& arg)
{
    f.count(10, arg);
}

struct counter
{
    template <class Sequence, class Kmerlist>
    void count(Sequence s, Kmerlist list)
    {
        cout << "primary" << endl;
    }
    
    template <class Sequence, class Kmerlist>
    void count(Sequence s, vector<Kmerlist> list)
    {
        cout << "vector" << endl;
    }
};




int main() 
{
    foo(counter(), 10);
    foo(counter(), vector<int>());
}

#include <initializer_list>
#include <iostream>
#include <cstddef>
#include <cassert>
#include <vector>
using namespace std;

struct Variadic
{
    size_t n;
    template<typename ...Args>
    void operator()(Args ...args)
    {
        assert(n == sizeof...(args) );
    }
};

Variadic fun(vector<int> x)
{
    return {x.size()};
}

int main()
{
    vector<int> x{1,2,3};
    fun(x)(1,2,3); // Runtime OK
    cout << "OK" << endl;
    fun(x)(1); // assert fail
}
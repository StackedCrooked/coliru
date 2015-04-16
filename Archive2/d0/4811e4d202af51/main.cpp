#include <boost/exception/detail/type_info.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/mpl/vector.hpp>
#include <iostream>
#include <cassert>
#include <vector>
#include <string>

using namespace boost;
using namespace std;

template<typename T>
T randomValue()
{
    return T();
}

struct Benchmark
{
    template<typename T>
    void operator()(T) const
    {
        cout << "Testing " << type_name<T>() << endl;
        vector<T> v;
        for(int i = 0; i < 3; ++i)
        {
           v.push_back(randomValue<T>());
        }
        assert(v.size() == 3);
    }
};

int main()
{
    mpl::for_each<mpl::vector<int, bool, string>>(Benchmark());
}
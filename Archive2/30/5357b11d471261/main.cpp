#include <boost/range/iterator_range.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/range/iterator.hpp>
#include <typeinfo>
#include <iostream>
#include <ostream>

using namespace boost;
using namespace std;

struct print
{
    template<typename T>
    void operator()(const T &t) const
    {
        cout << t << " ";
    }
};

int main()
{
    typedef int Array[20];
    cout << typeid( range_iterator<Array>::type ).name() << endl;

    Array arr={11,22,33,44,55,66,77,88};
    boost::for_each( make_iterator_range(arr,arr+5) ,print());
}

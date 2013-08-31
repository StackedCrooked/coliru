#include <boost/range/adaptor/transformed.hpp>
#include <boost/range/algorithm/copy.hpp>
#include <iostream>
#include <iterator>
#include <vector>

using namespace std;
using namespace boost;
using namespace adaptors;

struct AddressOf
{
    template<typename T>
    T *operator()(T &x) const
    {
        return &x;
    }
};

const auto &addressed = transformed(AddressOf{});

int main()
{
    int a[] = {11, 22, 33};
    vector<int*> b;
    
    copy(a | addressed, back_inserter(b));
    for(auto x : b)
        cout << *x << endl;
}

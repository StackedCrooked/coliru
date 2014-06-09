#include <boost/type_erasure/member.hpp>
#include <boost/type_erasure/any.hpp>
#include <boost/mpl/vector.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace boost;
using namespace type_erasure;

BOOST_TYPE_ERASURE_MEMBER((has_emplace_back), emplace_back, 1)

using container = any<has_emplace_back<void(int)>, _self&>;

void test(container x)
{
    x.emplace_back(1);
}

int main()
{
    vector<int> b{3, 4};
    test(b);
    for(auto x : b)
        cout << x << endl;
}
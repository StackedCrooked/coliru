#include <boost/exception/detail/type_info.hpp>
#include <boost/range/algorithm_ext.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/range/numeric.hpp>
#include <boost/timer/timer.hpp>
#include <exception>
#include <iostream>
#include <iterator>
#include <cstddef>
#include <vector>
#include <list>

/******************************************************************************/
using namespace std;
using namespace boost;

template<typename F>
void test(F f)
{
    timer::auto_cpu_timer t;
    for(int i=0; i != 1000; ++i)
    {
        volatile auto result = f();
        (void)result;
    }
}

struct Node
{
    Node *next = nullptr;
    unsigned x;
    
    Node(unsigned x = 0) : x(x) {}
};

int main() try
{
    auto constexpr N = 5000u;
    
    vector<Node> v(N);
    iota(v, 0u);

    for(auto &x : v)
        x.next = std::next(&x);
    v.back().next = &v.front();
    
    random_shuffle(v);
    
    test([&]
    {
        auto acc = 0u; 
        for(auto &x : v)
            acc += x.x;
        return acc;
    });
    test([&]
    {
        auto acc = 0u;
        auto p = &v.front();
        for(unsigned i = 0; i!=N; ++i)
        {
            acc += p->x;
            p = p->next;
        }
        return acc;
    });
}
catch(const exception &e)
{
    cout << e.what() << endl;
}

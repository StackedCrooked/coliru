#include <boost/range/algorithm.hpp>
#include <boost/coroutine/all.hpp>
#include <iostream>

using namespace std;
using namespace boost;
using namespace coroutines;

int main()
{    
    typedef coroutine<char> Coro;
    Coro::push_type coro([](Coro::pull_type &coro)
    {
        for_each(coro, [](auto x)
        {
            cout << x << endl;
        });
    });
    copy("1,2,3,4,5", begin(coro));
}

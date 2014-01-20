#include <boost/spirit/include/qi.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/coroutine/all.hpp>
#include <iostream>
#include <iterator>

using namespace std;
using namespace boost;
using namespace spirit;
using namespace coroutines;

int main()
{    
    using Coro = coroutine<char>;
    Coro::push_type coro([](Coro::pull_type &coro)
    {
        for_each(coro, [](char x){
            cout << x << endl;
        });
    });
    copy("abc", begin(coro));
}

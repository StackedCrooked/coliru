#include <iostream>
#include <boost/function.hpp>
using namespace std;


struct CallCounter
{
    CallCounter() : count( 0 ) {}
    void operator()()
    {
        // do stuff
        cout << "count is at " << count << endl;
        ++count;
    }

    int count;
};
//However, when I try to access count after passing it to another function, count is still at 0.

template<typename Functor>
void callNTimes( int n, Functor& func )
{
    for ( int i = 0; i < n; ++i )
        func();
}

int main()
{
    CallCounter counter;
    callNTimes( 20, counter );

    cout << counter.count << endl; // prints 0
    return 0;
}
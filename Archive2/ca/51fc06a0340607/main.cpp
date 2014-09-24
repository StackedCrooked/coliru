#include <boost/coroutine/all.hpp>
#include <iostream>
#include <future>
#include <thread>

using namespace boost;
using namespace std;

void print_tid(const char *x)
{
    cout << "Thread ID " << this_thread::get_id() << " in " << x << endl;
}

int main()
{
    print_tid("main begin");
    async(launch::async, []
    {
        coroutines::symmetric_coroutine<void>::call_type coro([](auto &yield)
        {
            print_tid("coro begin");
            yield();
            print_tid("coro end");
        });
        coro();
        return coro;
    }).get()();
    print_tid("main end");
}
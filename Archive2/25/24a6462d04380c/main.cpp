#include <iostream>
#include <memory>
#include <mutex>
#include <thread>
using namespace std;


struct X
{
    int n = 0;
    std::mutex mutex;
};

void run(X* x)
{
    for (size_t i = 0; i < 1000000; ++i)
    {
        std::lock_guard<std::mutex> (x->mutex);
        ++(x->n);
        std::this_thread::yield();
    }
}

int main()
{
    X x;
    std::thread t (run, &x);
    for (size_t i = 0; i < 1000000; ++i)
    {
        std::lock_guard<std::mutex> (x.mutex);
        --(x.n);
        std::this_thread::yield();
    }
    t.join();
    cout << x.n << endl;
    return 0;
}

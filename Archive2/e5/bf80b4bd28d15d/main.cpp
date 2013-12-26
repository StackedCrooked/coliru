#include <boost/thread/thread.hpp>
#include <iostream>
#include <queue>

using namespace boost;

template<typename T>
class concurrent_queue
{
    std::queue<T> q;
    mutable mutex m;
    mutable condition_variable c;
public:
    void push(const T &t)
    {
        lock_guard<mutex> l(m);
        q.push(t);
        c.notify_one();
    }
    void pop(T &result)
    {
        unique_lock<mutex> u(m);
        while(q.empty())
            c.wait(u);
        result = q.front();
        q.pop();
    }
};

int main()
{
    concurrent_queue<int> q;
    thread producer([&]
    {
        for(int i = 1024; i>=0; --i)
        {
            q.push(i);
            this_thread::yield();
        }
    });
    try
    {
        using namespace std;
        int x;
        while(q.pop(x), x)
        {
            cout << x << endl;
            this_thread::yield();
        }
        cout << "finish" << endl;
    } catch(...){}
    producer.join();
}

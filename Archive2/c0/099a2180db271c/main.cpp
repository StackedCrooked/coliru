#include <boost/lockfree/spsc_queue.hpp>
#include <boost/optional.hpp>
#include <boost/variant.hpp>

#include <condition_variable>
#include <iostream>
#include <cstddef>
#include <thread>
#include <chrono>
#include <mutex>

using namespace std;

/*********************************************/
template<typename T, size_t N>
class concurrent_queue
{
    mutable boost::lockfree::spsc_queue<T, boost::lockfree::capacity<N>> q;
    mutable mutex m;
    mutable condition_variable c;

    void wait() const
    {
        unique_lock<mutex> u(m);
        c.wait_for(u, chrono::microseconds(1));
    }
    void notify() const
    {
        c.notify_one();
    }
public:
    void push(const T &t)
    {
        while(!q.push(t))
            wait();
        notify();
    }
    void pop(T &result)
    {
        while(!q.pop(result))
            wait();
        notify();
    }
};

/*********************************************/
template<typename T, typename F>
class concurrent
{
    typedef boost::optional<F> Job;

    mutable concurrent_queue<Job, 16> q; // use custom size
    mutable T x;
    thread worker;

public:
    concurrent(T x)
        : x{x}, worker{[this]
        {
            Job j;
            while(true)
            {
                q.pop(j);
                if(!j) break;
                (*j)(this->x); // you may need to handle exceptions in some way
            }
        }}
    {}
    void operator()(const F &f)
    {
        q.push(Job{f});
    }
    ~concurrent()
    {
        q.push(Job{});
        worker.join();
    }
};

/*********************************************/
struct LogEntry
{
    struct Formatter
    {
        typedef void result_type;
        ostream *out;

        void operator()(double x) const
        {
            *out << "floating point: " << x << endl;
        }
        void operator()(int x) const
        {
            *out << "integer: " << x << endl;
        }
    };
    boost::variant<int, double> data;

    void operator()(ostream *out)
    {
        boost::apply_visitor(Formatter{out}, data);
    }
};

/*********************************************/
int main()
{
    concurrent<ostream*, LogEntry> log{&cout};

    for(int i=0; i!=1024; ++i)
    {
        log({i});
        log({i/10.});
    }
}

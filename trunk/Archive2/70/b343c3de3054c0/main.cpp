#define BOOST_THREAD_PROVIDES_SIGNATURE_PACKAGED_TASK
#include <boost/thread.hpp>
#include <boost/thread/future.hpp>

namespace th = boost;

using T = int;

struct S {
    th::packaged_task<T()> task;
    th::unique_future<T> future;
    void start();
    void stop();
};

void S::start() {
    task = th::packaged_task<T()>{ [] () {
        thread_local struct X { ~X() { std::cout << "destructing thread_locals\n"; } } stuff;
        std::cout << "executing\n";
        return T();
    }};
    future = task.get_future();                
    task.make_ready_at_thread_exit();
}

void S::stop() {
    future.wait();                
}

int main() {
    {
        S s;
        std::cout << "enter\n";
        s.start();
        std::cout << "started\n";
        s.stop();
        std::cout << "stopped\n";
    }
    std::cout << "leave\n";
}

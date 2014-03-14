#define BOOST_THREAD_PROVIDES_SIGNATURE_PACKAGED_TASK
#include <boost/thread.hpp>
#include <boost/thread/future.hpp>

namespace th = boost;

using T = int;

struct S {
    th::packaged_task<T()> task;
    th::unique_future<T> future;
    boost::thread start();
    void stop();
};

boost::thread S::start() {
    return boost::thread([this] {
        task = th::packaged_task<T()>{ [] {
            thread_local struct X { ~X() { std::cout << "destructing thread_locals\n"; } } stuff;
            std::cout << "executing\n";
            return T();
        }};
        future = task.get_future();                
        task.make_ready_at_thread_exit();
    });
}

void S::stop() {
    future.wait();                
}

int main() {
    {
        S s;
        std::cout << "enter\n";
        auto th = s.start();
        std::cout << "started\n";
        th.join();
        s.stop();
        std::cout << "stopped\n";
    }
    std::cout << "leave\n";
}

#include <cstddef>
#include <functional>
#include <tbb/concurrent_queue.h>
#include <thread>
#include <vector>

class ThreadPool {
public:
    ThreadPool(std::size_t n) {
        threads.reserve(n);
        for (std::size_t i = 0; i < n; ++i) {
            threads.push_back(std::thread([this] {
                for (;;) {
                    std::function<void()> function;
                    queue.pop(function);
                    function();
                }
            }));
        }
    }

    template<typename F>
    void schedule(F f) {
        queue.push(f);
    }

private:
    std::vector<std::thread> threads;
    tbb::concurrent_bounded_queue<std::function<void()>> queue;
};

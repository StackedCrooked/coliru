#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <cassert>
#include <cstddef>
#include <utility>

class thread_pool {
public:
    explicit thread_pool(std::size_t thread_count) : work(io_service) {
        assert(thread_count > 0);
        for (decltype(thread_count) i = 0; i < thread_count; ++i) {
            thread_group.create_thread([this] {
                io_service.run();
            });
        }
    }

    ~thread_pool() {
        io_service.stop();
        thread_group.join_all();
    }

    template<typename F>
    void post(F&& f) {
        io_service.post(std::forward<F>(f));
    }

private:
    boost::thread_group thread_group;
    boost::asio::io_service io_service;
    boost::asio::io_service::work work;
};

#include <atomic>
#include <iostream>

int main() {
    std::atomic<int> x;
    thread_pool pool(4);
    for (int i = 0; i < 1000; ++i) {
        pool.post([&] {
            ++x;
        });
    }
    std::cout << x << '\n';
    return 0;
}

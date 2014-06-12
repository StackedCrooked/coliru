#include <iostream>
#include <chrono>
#include <condition_variable>
#include <thread>
#include <mutex>
#include <memory>
#include <utility>

using interval_t = std::chrono::milliseconds;
constexpr struct start_now_t {} start_now;

template <typename Function>
class interval_timer {
    class impl {
        Function f;
        const interval_t interval;
        std::thread thread;
        std::mutex mtx;
        std::condition_variable cvar;
        bool enabled = false;
    
        void timer() {
            auto deadline = std::chrono::steady_clock::now() + interval;
            std::unique_lock<std::mutex> lock{mtx};
            while (enabled) {
                if (cvar.wait_until(lock, deadline) == std::cv_status::timeout) {
                    lock.unlock();
                    f();
                    deadline += interval;
                    lock.lock();
                }
            }
        }
    
    public:
        impl(Function f, interval_t interval) :
          f(std::move(f)), interval(std::move(interval)) {}
    
        ~impl() {
            stop();
        }
        
        void start() {
            if (!enabled) {
                enabled = true;
                thread = std::thread(&impl::timer, this);
            }
        }
        
        void stop() {
            if (enabled) {
                {
                    std::lock_guard<std::mutex> _{mtx};
                    enabled = false;
                }
                cvar.notify_one();
                thread.join();
            }
        }
    };

    std::unique_ptr<impl> pimpl;

public:
    interval_timer(Function f, interval_t interval) :
        pimpl{new impl(std::move(f), std::move(interval))} {}

    interval_timer(Function f, interval_t interval, start_now_t) :
        pimpl{new impl(std::move(f), std::move(interval))} {
        start();
    }

    void start() { pimpl->start(); }
    void stop() { pimpl->stop(); }
};

template <typename Function, typename... Args>
interval_timer<typename std::decay<Function>::type>
make_interval_timer(Function&& f, Args&&... args) {
    return {std::forward<Function>(f), std::forward<Args>(args)...};
}

int main() {
    auto timer1 = make_interval_timer([]{ std::cout << "tick\n"; }, std::chrono::milliseconds{500}, start_now);
    auto timer2 = make_interval_timer([]{ std::cout << "tock\n"; }, std::chrono::milliseconds{500});
    timer2.start();
    for (auto i = 0; i < 5; ++i) {
        std::this_thread::sleep_for(std::chrono::seconds{1});
        std::cout << "CLANG\n";
    }
}

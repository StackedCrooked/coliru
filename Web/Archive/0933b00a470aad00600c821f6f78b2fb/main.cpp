#include <future>
#include <thread>
#include <functional>

template <typename Signature>
class async_task;

template <typename Result, typename... Args>
class async_task<Result(Args...)> {
public:
    using signature_type = Result(Args...);

    template <typename Fun>
    explicit async_task(Fun&& fun)
    : fun(std::forward<Fun>(fun)) {}

    std::future<Result> operator()(Args... args) const {
        std::packaged_task<signature_type> task(fun);
        auto result = task.get_future();
        std::thread(std::move(task), std::forward<Args>(args)...).detach(); // no cancellation? :(
        return result;
    }
    
private:
    std::function<signature_type> fun;
};

#include <random>
#include <chrono>
#include <iostream>
#include <cstddef>

int main()
{
    async_task<int(int)> async_d6{[&](std::size_t seed) -> int {
        std::mt19937 generator{seed};
        std::uniform_int_distribution<int> distribution{1, 6};
        auto r = distribution(generator);
        std::this_thread::sleep_for(std::chrono::seconds(r));
        std::cout << "Slept for " << r << " seconds.\n"; // race on purpose
        return r;
    }};
    auto die1 = async_d6(0);
    auto die2 = async_d6(1);
    std::cout << "Total is: " << die1.get() + die2.get();
}
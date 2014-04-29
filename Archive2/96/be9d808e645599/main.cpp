#include <thread>
#include <future>
#include <iostream>
#include <random>

using namespace std;

struct my_failure : virtual std::exception {
    char const* what() const noexcept { return "the thread failed randomly"; }
};

int my_processing_task() // this can randomly fail
{
    static const size_t iterations = 1ul << 4;
    static const size_t mtbf       = iterations << 2; // 25% chance of failure
    static auto odds = bind(uniform_int_distribution<size_t>(0, mtbf), mt19937(time(NULL)));

    for(size_t iteration = 0; iteration < iterations; ++iteration)
    {
        // long task
        this_thread::sleep_for(chrono::milliseconds(10));

        // that could fail
        if (odds() == 37) 
            throw my_failure();
    }

    // we succeeded!
    return 42;
}

std::atomic_bool shutdown(false);
std::atomic_size_t failures(0), completions(0);

template <typename F> void monitor_task_loop(F f)
{
    while (!shutdown)
    try {
        f();
        ++completions;
    } catch (exception const& e)
    {
        std::cout << "handling: '" << e.what() << "'\n";
        ++failures;
    }
    std::cout << "shutdown requested\n";
}

int main()
{
    auto monitor = [] { monitor_task_loop(my_processing_task); };
    thread t1(monitor), t2(monitor), t3(monitor);

    this_thread::sleep_for(chrono::seconds(3));
    shutdown = true;

    t1.join();
    t2.join();
    t3.join();

    std::cout << "completions: " << completions << ", failures: " << failures << "\n";
}

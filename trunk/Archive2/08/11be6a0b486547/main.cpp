#include <boost/thread.hpp>
#include <boost/random.hpp>
#include <boost/bind.hpp>
#include <iostream>

using namespace boost;

struct my_failure : virtual std::exception {
    char const* what() const throw() { return "the thread failed randomly"; }
};

int my_processing_task() // this can randomly fail
{
    static const size_t iterations = 1ul << 4;
    static const size_t mtbf       = iterations << 2; // 25% chance of failure
    static function<size_t()> odds = bind(random::uniform_int_distribution<size_t>(0, mtbf), mt19937(time(NULL)));

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

atomic_bool shutdown(false);
atomic_size_t failures(0), completions(0);

struct monitor_task_loop {
    typedef void result_type;

    template <typename F> void operator()(F f) const
    {
        while (!shutdown)
        try {
            f();
            ++completions;
        } catch (std::exception const& e)
        {
            std::cout << "handling: '" << e.what() << "'\n";
            ++failures;
        }
        std::cout << "shutdown requested\n";
    }
};

int main()
{
    thread_group g;
    for (int i=0; i<3; ++i)
        g.create_thread(bind(monitor_task_loop(), my_processing_task));

    this_thread::sleep_for(chrono::seconds(3));
    shutdown = true;

    g.join_all();

    std::cout << "completions: " << completions << ", failures: " << failures << "\n";
}

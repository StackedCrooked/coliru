#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include <future>
#include <chrono>


boost::asio::io_service ios;


struct Dispatcher
{
    Dispatcher() :
        mStrand(ios)
    {
    }

    // post without return value
    template<typename F>
    void post_no_return(F&& f)
    {
        mStrand.post([f]{ f(); });
    }

    // post with return value wrapped in a future
    template<typename F>
    auto post(F&& f) -> std::future<decltype(f())>
    {
        using R = decltype(f());
        using Task = std::packaged_task<R()>;
        auto task = std::make_shared<Task>(std::forward<F>(f));
        auto fut = task->get_future();
        mStrand.post([task]{ (*task)(); });
        return fut;
    }

    // post with delay
    template<typename F>
    auto post_after(F&& f, boost::posix_time::milliseconds delay) -> std::future<decltype(f())>
    {
        using R = decltype(f());

        auto tp = std::make_shared<DelayedTask<R>>(std::forward<F>(f));
        auto fut = tp->task.get_future();

        boost::system::error_code ec;
        tp->timer.expires_from_now(delay, ec);
        tp->timer.async_wait(mStrand.wrap([tp](boost::system::error_code) { tp->task(); }));
        return fut;
    }

private:
    using Timer = boost::asio::deadline_timer;

    template<typename R>
    using Task = std::packaged_task<R()>;

    template<typename R>
    struct DelayedTask
    {
        template<typename FF>
        DelayedTask(FF&& ff) : task(std::forward<FF>(ff)), timer(ios) {}

        Task<R> task;
        Timer timer;
    };

    boost::asio::io_service::strand mStrand;
};



int main()
{


    Dispatcher dispatcher1;

    boost::thread_group threads;

    auto work = std::make_shared<boost::asio::io_service::work>(ios);

    // Dispatcher is powered by threads.
    for (int i = 0; i != 8; ++i)
    {
        threads.create_thread([]{ ios.run(); });
    }


    // Test post without return value
    std::cout << "\nTesting simple task with post_no_return()\n => " << std::flush;
    std::atomic<int> n{0}; dispatcher1.post_no_return([&n] { n = 1; }); while (n != 1) {}
    std::cout << "n=" << n << std::endl;


    // Test post with return value
    std::cout
        << "\nTesting task with future return value using post()\n => " << std::flush
        << dispatcher1.post([]{ return 42; }).get()
        << std::endl;


    // Test delayed post
    using namespace std::chrono;
    auto start_time = steady_clock::now();
    std::cout
        << "\nTesting delayed task with post_after()\n => " << std::flush
        << dispatcher1.post_after([start_time] {
                return duration_cast<milliseconds>(steady_clock::now() - start_time).count();
            }, boost::posix_time::milliseconds(50)).get()
        << " milliseconds have elapsed." << std::endl;


    // Testing thread-safety (of io_service::strand)
    std::cout << "\nTesting multiple tasks on one strand:\n => " << std::flush;
    for (int i = 0; i != 10; ++i)
    {
        dispatcher1.post_no_return([i]{ std::cout << 1; });
        dispatcher1.post_no_return([i]{ std::cout << 2; });
        dispatcher1.post_no_return([i]{ std::cout << 3; });
        dispatcher1.post_no_return([i]{ std::cout << 4 << ' '; });
    }

    // Wait for the disptacher to finish above jobs.
    dispatcher1.post([]{}).get();


    // Testing multiple thread-unsafety with multiple strands:

    std::cout << std::endl << "\nTesting multiple tasks on multiple strands (introducing race conditions on std::cout)\n => " << std::flush;
    Dispatcher dispatcher2;
    Dispatcher dispatcher3;
    Dispatcher dispatcher4;
    for (int i = 0; i != 10; ++i)
    {
        dispatcher1.post_no_return([i]{ std::cout << 1; });
        dispatcher2.post_no_return([i]{ std::cout << 2; });
        dispatcher3.post_no_return([i]{ std::cout << 3; });
        dispatcher4.post_no_return([i]{ std::cout << 4 << ' '; });
    }

    // Waiting for all four dispatchers to finish above jobs.
    dispatcher1.post([]{}).get();
    dispatcher2.post([]{}).get();
    dispatcher3.post([]{}).get();
    dispatcher4.post([]{}).get();

    std::cout << "\n\nPerforming cleanup." << std::endl;
    work.reset();
    threads.join_all();
    std::cout << "Done." << std::endl;
}

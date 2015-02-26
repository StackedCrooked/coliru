#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include <tbb/scalable_allocator.h>
#include <future>
#include <chrono>


boost::asio::io_service& GetIOService()
{
    static boost::asio::io_service fIOService;
    return fIOService;
}


struct Internal {};


struct Scheduler
{
    Scheduler(boost::asio::io_service& ios) :
        mStrand(ios)
    {
    }

    template<typename F>
    void post_no_return(F&& f)
    {
        mStrand.post([f]{ f(Internal{}); });
    }

    template<typename F>
    auto post(F&& f) -> std::future<decltype(f(std::declval<Internal>()))>
    {
        using R = decltype(f(std::declval<Internal>()));
        using Task = std::packaged_task<R(Internal)>;
        tbb::scalable_allocator<char> alloc;
        auto task = std::allocate_shared<Task>(alloc, std::allocator_arg, alloc, std::forward<F>(f));
        auto fut = task->get_future();
        mStrand.post([task]{ (*task)(Internal{}); });
        return fut;
    }

    template<typename F>
    auto post_after(F&& f, boost::posix_time::milliseconds delay) -> std::future<decltype(f(std::declval<Internal>()))>
    {
        using R = decltype(f(std::declval<Internal>()));
        
        tbb::scalable_allocator<char> alloc;
        
        auto tp = std::allocate_shared<DelayedTask<R>>(alloc, alloc, std::forward<F>(f));
        auto fut = tp->task.get_future();
        
        boost::system::error_code ec;
        tp->timer.expires_from_now(delay, ec);
        tp->timer.async_wait(mStrand.wrap([tp](boost::system::error_code) { tp->task(Internal{}); }));
        return fut;
    }
    
private:
    using Timer = boost::asio::deadline_timer;

    template<typename R>
    using Task = std::packaged_task<R(Internal)>;
    
    template<typename R>
    struct DelayedTask
    {
        template<typename Alloc, typename FF>
        DelayedTask(Alloc alloc, FF&& ff) : task(std::allocator_arg, alloc, std::forward<FF>(ff)), timer(GetIOService()) {}
        
        Task<R> task;
        Timer timer;
    };  

    boost::asio::io_service::strand mStrand;
};




int main()
{
    Scheduler scheduler(GetIOService());
    boost::thread_group threadGroup;
    boost::asio::io_service::work work(GetIOService());
    threadGroup.create_thread([]{ GetIOService().run(); });
    threadGroup.create_thread([]{ GetIOService().run(); });
    threadGroup.create_thread([]{ GetIOService().run(); });
    threadGroup.create_thread([]{ GetIOService().run(); });

    scheduler.post_no_return([](Internal){
        std::cout << "I'm in a post_no_return!" << std::endl;
    });

    scheduler.post([](Internal) -> std::ostream& {
        return std::cout << "I'm in a pos";
    }).get() << "t with return!" << std::endl;

    scheduler.post_after([](Internal) {
        std::cout << "I'm in a delayed post!" << std::endl;
    }, boost::posix_time::milliseconds(10)).get();

    threadGroup.join_all();
    std::cout << "End of program." << std::endl;
}

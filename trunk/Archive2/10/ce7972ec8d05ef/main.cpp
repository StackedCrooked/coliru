#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include <future>
#include <chrono>

boost::asio::io_service& GetIOService()
{
    static boost::asio::io_service fIOService;
    return fIOService;
}


using Seconds = std::chrono::seconds;

struct Internal {};

struct Scheduler2
{
    Scheduler2(boost::asio::io_service& ios) :
        mStrand(ios)
    {
    }

    template<typename F>
    void dispatch_no_return(F&& f)
    {
        mStrand.post([f]{ f(Internal{}); });
    }

    template<typename F>
    auto dispatch(F&& f) -> std::future<decltype(f(std::declval<Internal>()))>
    {
        using R = decltype(f(std::declval<Internal>()));
        using Prom = std::packaged_task<R(Internal)>;
        auto prom = std::make_shared<Prom>(std::forward<F>(f));
        auto fut = prom->get_future();
        mStrand.post([prom]{ (*prom)(Internal{}); });
        return fut;
    }

    template<typename F>
    auto schedule(F&& f, boost::posix_time::milliseconds delay) -> std::future<decltype(f(std::declval<Internal>()))>
    {
        using R = decltype(f(std::declval<Internal>()));
        using Prom = std::packaged_task<R(Internal)>;
        auto prom = std::make_shared<Prom>(std::forward<F>(f));
        auto fut = prom->get_future();
        auto timer = std::make_shared<boost::asio::deadline_timer>(GetIOService());
        boost::system::error_code ec;
        timer->expires_from_now(delay, ec);
        timer->async_wait(mStrand.wrap([prom, timer](boost::system::error_code) { (*prom)(Internal{}); }));
        return fut;
    }

    boost::asio::io_service::strand mStrand;
};


Scheduler2 scheduler(GetIOService());


int main()
{
    boost::thread_group threadGroup;
    {
        boost::asio::io_service::work work(GetIOService());
        threadGroup.create_thread([]{ GetIOService().run(); });
        threadGroup.create_thread([]{ GetIOService().run(); });
        threadGroup.create_thread([]{ GetIOService().run(); });
        threadGroup.create_thread([]{ GetIOService().run(); });

        std::cout << "ICMPTest" << std::endl;

        scheduler.dispatch_no_return([](Internal){
            std::cout << "I'm in a task!" << std::endl;
        });

        scheduler.dispatch([](Internal in) {
            std::cout << "I'm in a DISPATCH task!" << std::endl;
            return in;
        }).get();

        using ms = boost::posix_time::milliseconds;

        scheduler.schedule([](Internal) {
            std::cout << "YAY I'm in a SCHEDULE task!" << std::endl;
            return scheduler.schedule([](Internal) {
                std::cout << "YAY I'm in a SCHEDULE task!" << std::endl;
                return scheduler.schedule([](Internal in) {
                    std::cout << "YAY I'm in a SCHEDULE task!" << std::endl;
                    return in;
                }, ms(12));
            }, ms(12));
        }, ms(12)).get().get().get(); // join nested schedules
    }



    std::cout << "Joining threads." << std::endl;
    threadGroup.join_all();
    std::cout << "Joined threads." << std::endl;
}

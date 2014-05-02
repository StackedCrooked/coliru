#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/optional.hpp>
#include <boost/make_shared.hpp>

struct LogonMonitor {
    LogonMonitor() 
        : work(io_service::work(replyService)), background([this]{ replyService.run(); })
    { }

    ~LogonMonitor() {
        work = boost::none;
        background.join();
    }

    void foo(int clientId) {
        shared_timer& timer = timersByClientId[clientId];

        if (!timer) 
            onLogonChangeCallback(clientId, true);

        timer = make_timer(); // reset

        timer->async_wait([this, clientId](const boost::system::error_code& err) {
            if (!err)
                onLogonChangeCallback(clientId, false);
            else
                std::cout << "(cancel " << clientId << " timer)" << std::endl;
        });
    }

  private:
    using io_service   = boost::asio::io_service;
    using timer        = boost::asio::deadline_timer;
    using shared_timer = boost::shared_ptr<timer>;

    io_service replyService;
    boost::optional<io_service::work> work;
    boost::thread background;

    std::map<int, shared_timer> timersByClientId;

    shared_timer make_timer() { 
        return boost::make_shared<timer>(replyService, boost::posix_time::seconds(/*6*/1)); 
    }

    void onLogonChangeCallback(int clientId, bool newLogon) 
    {
        std::cout << __FUNCTION__ << "(" << clientId << ", " << newLogon << ")" << std::endl;
    }
};

int main()
{
    LogonMonitor instance;
    for (int i = 0; i < 100; ++i)
    {
        instance.foo(rand() % 16);
        boost::this_thread::sleep_for(boost::chrono::milliseconds(rand() % 10));
    }
}
